[![Latest Release](https://img.shields.io/github/v/release/lungu19/ThrowbackLoader?include_prereleases)](https://github.com/lungu19/ThrowbackLoader/releases)[![License: GPL3](https://img.shields.io/badge/License-GPL3-yellow.svg)](https://opensource.org/license/gpl-3-0)
# ThrowbackLoader
ThrowbackLoader is the software used by the [Rainbow Six Siege Throwback](https://discord.gg/yxpT6EChgr) project to allow to launch any old version of Rainbow Six Siege offline.

## Instructions
> [!WARNING]
> ⚠️You **must own** a copy of Rainbow Six Siege. 
>  You **must** use this software only on a **legally obtained** copy of Siege (e.g. Steam or Steam DepotDownloader). Any copy obtained illegally or games other than Rainbow Six Siege are **NOT** supported.

Download the latest version of ThrowbackLoader from the [**Releases Page**](https://github.com/lungu19/ThrowbackLoader/releases), extract it and read the README file.
## Building from Source
### Prerequisites
- A Windows 10 or 11 machine
- An up-to-date installation of Visual Studio
- An up-to-date installation of Clang-CL
### Steps
1. Open the Visual Studio Developer Powershell.
2. Clone the repository:
```powershell
git clone https://github.com/lungu19/ThrowbackLoader.git
cd ThrowbackLoader
```
3. Eventually edit `Directory.build.props` to point to your Clang-CL installation and change the Clang version in VS.
4. Build the release by running the `package_release.ps1` Powershell script inside of the Visual Studio Developer Powershell
The release archive will be located in the project folder and it will be called `ThrowbackLoader.zip``.

## Known Issues
- After installing ThrowbackLoader on Y1S1 Black Ice for the first time, the menu will be unresponsive. Reboot to fix. Only happens on first launch.

## License
This project is licensed under the GPL3 License - see the [LICENSE](https://github.com/lungu19/ThrowbackLoader/LICENSE) file for details.

## Credits
- The Uplay R1 emulator is based on `ColdPlay_Uplay` by Rat431, with additional help from Zer0Bytes.
- The Uplay R2 emulator is based on `Goldberg uplay r2 Open Source v0.0.1` by Mr_Goldberg.
- ThrowbackLoader releases bundle a copy of [gbe_fork](https://github.com/Detanup01/gbe_fork).

## Disclaimer
This software is an independent project and is not affiliated with, endorsed by, or sponsored by Ubisoft Entertainment.
*Rainbow Six Siege* and all related names, logos, and assets are trademarks or registered trademarks of Ubisoft Entertainment in the U.S. and/or other countries. All rights belong to their respective owners.
