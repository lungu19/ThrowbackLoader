Clear-Host

$basePath = $PWD.Path

$downloadUrl = "https://gitlab.com/Mr_Goldberg/goldberg_emulator/-/jobs/4247811310/artifacts/download"

$extractPath = Join-Path -Path $basePath -ChildPath "goldberg_emu"
$archivePath = Join-Path -Path $basePath -ChildPath "goldberg_emu.zip"

if (Test-Path -Path $extractPath) {
    Write-Host "GbEmu directory '$extractPath' already exists. Skipping." -ForegroundColor Green
} else {
    try {
        Write-Host "Downloading GbEmu" -ForegroundColor Cyan
        Invoke-WebRequest -Uri $downloadUrl -OutFile $archivePath
        Write-Host "Download complete: $archivePath"
        Write-Host "Extracting archive..." -ForegroundColor Cyan
        Expand-Archive -Path $archivePath -DestinationPath $extractPath -Force
        Write-Host "Successfully extracted GbEmu to '$extractPath'" -ForegroundColor Green
    }
    catch {
        Write-Error "Failed to download or extract GbEmu. Error: $_"
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

# copy GbEmu emu artifact
Copy-Item $extractPath\steam_api64.dll (Join-Path -Path $outputFolder -ChildPath "steam_api64.dll")

# build solution and get artifacts
msbuild .\ThrowbackLoader.slnx /maxCpuCount /nologo /property:Configuration=Release /property:Platform="x64" /target:Rebuild
Copy-Item .\x64\Release\upc_r1_loader64.dll (Join-Path -Path $outputFolder -ChildPath "upc_r1_loader64.dll")
Copy-Item .\x64\Release\upc_r2_loader64.dll (Join-Path -Path $outputFolder -ChildPath "upc_r2_loader64.dll")
Copy-Item .\x64\Release\uplay_r1_loader64.dll (Join-Path -Path $outputFolder -ChildPath "uplay_r1_loader64.dll")
Copy-Item .\x64\Release\defaultargs.dll (Join-Path -Path $outputFolder -ChildPath "defaultargs.dll")

# copy README, default config and Launch bat
Copy-Item .\assets\README.txt (Join-Path -Path $outputFolder -ChildPath "README.txt")
Copy-Item .\assets\default_config.toml (Join-Path -Path $outputFolder -ChildPath "ThrowbackLoader.toml")
Copy-Item .\assets\LaunchR6.bat (Join-Path -Path $outputFolder -ChildPath "LaunchR6.bat")

# create zip archive
$outputZip = Join-Path -Path $basePath -ChildPath "ThrowbackLoader_$versionString.zip"
Compress-Archive -Path "$outputFolder\*" -DestinationPath $outputZip -Force

# cleanup
if (Test-Path -Path $archivePath) {
    Write-Host "Cleaning up downloaded GbEmu archive '$archivePath'..."
    Remove-Item -Path $archivePath -Force
}

if (Test-Path -Path $outputFolder) {
    Write-Host "Cleaning up output folder '$outputFolder'..."
    Remove-Item -Path $outputFolder -Recurse -Force
}