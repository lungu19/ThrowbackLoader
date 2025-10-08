Clear-Host

$basePath = $PWD.Path

$downloadUrl = "https://api.github.com/repos/Detanup01/gbe_fork/releases/latest"
$assetName = "emu-win-release.7z"

$extractPath = Join-Path -Path $basePath -ChildPath "gbe_fork"
$archivePath = Join-Path -Path $basePath -ChildPath "gbe_fork_latest.7z"

if (Test-Path -Path $extractPath) {
    Write-Host "GbeFork directory '$extractPath' already exists. Skipping." -ForegroundColor Green
} else {
    $sevenZipPath = Get-Command 7z.exe -ErrorAction SilentlyContinue
    if (-not $sevenZipPath) {
        Write-Error "7-Zip (7z.exe) is not found in your system's PATH. Please install 7-Zip and add it to your PATH to continue."
        throw "Dependency missing: 7-Zip"
    }
    try {
        Write-Host "Fetching latest GbeFork release information..."
        $latestRelease = Invoke-WebRequest -Uri $downloadUrl -UseBasicParsing | ConvertFrom-Json
        $asset = $latestRelease.assets | Where-Object { $_.name -eq $assetName }
        if (-not $asset) {
            Write-Error "Could not find the asset '$assetName' in the latest release."
            throw "Asset not found"
        }
        Write-Host "Downloading GbeFork asset: $assetName" -ForegroundColor Cyan
        Invoke-WebRequest -Uri $asset.browser_download_url -OutFile $archivePath
        Write-Host "Download complete: $archivePath"
        Write-Host "Extracting archive..." -ForegroundColor Cyan
        & $sevenZipPath.Source x $archivePath -o"$extractPath" -y | Out-Null
        Write-Host "Successfully extracted GbeFork to '$extractPath'" -ForegroundColor Green
    }
    catch {
        Write-Error "Failed to download or extract GbeFork. Error: $_"
        throw $_
    }
}


$versionParts = @{}

Get-Content -Path ".\Core\Core.h" | ForEach-Object {
    switch -Regex ($_) {
        '^\s*#define\s+TB_LOADER_MAJOR\s+(.+)'      { $versionParts.Major = $matches[1].Trim() }
        '^\s*#define\s+TB_LOADER_MINOR\s+(.+)'      { $versionParts.Minor = $matches[1].Trim() }
        '^\s*#define\s+TB_LOADER_PATCH\s+(.+)'      { $versionParts.Patch = $matches[1].Trim() }
        '^\s*#define\s+TB_LOADER_METADATA\s+(.+)'   { $versionParts.Metadata = $matches[1].Trim().Trim('"') }
    }
}

if (-not ($versionParts.ContainsKey('Major') -and $versionParts.ContainsKey('Minor') -and $versionParts.ContainsKey('Patch'))) {
    Write-Error "Could not find all required version components (MAJOR, MINOR, PATCH) in '$Path'."
    exit
}

$versionString = "{0}.{1}.{2}" -f $versionParts.Major, $versionParts.Minor, $versionParts.Patch

if ($versionParts.ContainsKey('Metadata') -and -not [string]::IsNullOrWhiteSpace($versionParts.Metadata)) {
    $versionString += "-$($versionParts.Metadata)"
}


# create output director
$outputFolder = Join-Path -Path $basePath -ChildPath "output"
if (Test-Path -Path $outputFolder) {
    Write-Host "Folder exists. Removing it..."
    Remove-Item -Path $outputFolder -Recurse -Force
}
New-Item -Path $outputFolder -ItemType Directory

# copy gbefork emu artifact
Copy-Item .\gbe_fork\release\regular\x64\steam_api64.dll (Join-Path -Path $outputFolder -ChildPath "steam_api64.dll")

# build solution and get artifacts
msbuild .\ThrowbackLoader.slnx /maxCpuCount /nologo /property:Configuration=Release /property:Platform="x64" /target:Rebuild
Copy-Item .\x64\Release\upc_r1_loader64.dll (Join-Path -Path $outputFolder -ChildPath "upc_r1_loader64.dll")
Copy-Item .\x64\Release\upc_r2_loader64.dll (Join-Path -Path $outputFolder -ChildPath "upc_r2_loader64.dll")
Copy-Item .\x64\Release\uplay_r1_loader64.dll (Join-Path -Path $outputFolder -ChildPath "uplay_r1_loader64.dll")
Copy-Item .\x64\Release\defaultargs.dll (Join-Path -Path $outputFolder -ChildPath "defaultargs.dll")

# copy README, default config and Launch bat
Copy-Item .\Core\README.txt (Join-Path -Path $outputFolder -ChildPath "README.txt")
Copy-Item .\Core\default_config.toml (Join-Path -Path $outputFolder -ChildPath "ThrowbackLoader.toml")
Copy-Item .\Core\LaunchR6.bat (Join-Path -Path $outputFolder -ChildPath "LaunchR6.bat")

# create zip archive
$outputZip = Join-Path -Path $basePath -ChildPath "ThrowbackLoader_$versionString.zip"
Compress-Archive -Path "$outputFolder\*" -DestinationPath $outputZip -Force

# cleanup
if (Test-Path -Path $archivePath) {
    Write-Host "Cleaning up downloaded GbeFork archive '$archivePath'..."
    Remove-Item -Path $archivePath -Force
}

if (Test-Path -Path $outputFolder) {
    Write-Host "Cleaning up output folder '$outputFolder'..."
    Remove-Item -Path $outputFolder -Recurse -Force
}