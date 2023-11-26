# Touhou Danmakufu-V
A fork of Danmakufu ph3.5 aiming to provide better functionality to the engine, such as general improvements and others including new features, like Netplay.<br>
All readme-like documents have been translated from Japanese to English by the repository owner himself.<br>
Multiplatform support is also planned for Windows, macOS and Linux; the [linux](https://github.com/gmestanley/DNH-V/tree/linux/) branch is in development and is set to be used for the last one, but is still a heavy work in progress. Currently only Windows is supported with the master branch.

## Changelog
Aside from the current releases, there were changes made in older versions; check the older repository [DNH-Netplay](https://github.com/gmestanley/DNH-Netplay) to see a log of them.

###### [0.6.2]
 * Error-catching in the Netplay functions' logging improved
 * LocalNetData renamed to GetLocalNetData
 * Implemented new function SetLocalNetData
    - Sets any data recently saved by ReceiveNetData to a string specified in the first argument.

###### [0.6.1]
 * Branding updated
 	- Title was changed from "DNH Netplay" to "DNH-V", and further mentions of "Netplay" were also replaced with that.
 * Translations of the Readme and adjacent documents provided (along with the original forms)
 * Example script for Netplay functionality provided (misplaced in script/sample/)
 * VS Projects upgraded to Visual Studio 2019

## Requirements (for compiling)
 * zlib
</br>(Quoted from Danmakufu Woo's repo) Best and recommended way to obtain it is to use [vcpkg](https://github.com/Microsoft/vcpkg) C++ Library Manager.
 * sfml
</br>Get it here: https://sfml-dev.org
</br>Also deserves credit because it was used to implement netplay in the first place.

## Known Issues
 * Script functions do not work (top priority, is being fixed)
 * Wine 4.12.1 (confirmed on macOS at least) suffers some scaling problems with the window size, being 9 pixels too wide and 7 pixels too tall.  This causes some nasty scaling on in-game assets, possibly a result of old Windows size calls not being 100% compatible with Wine releases.
 * The exe will crash when trying to load a sound file that is both: not 1411kbs and is stereo (fixed in Woo; fix will be brought over soon)

## Special Thanks
WishMakers - for making Danmakufu Woo and helping me with this project<br>
Mana - provided the fix for ItoA and IntToString's int range

## Contact
If you want to talk about the project, check out its Discord server: https://discord.gg/W93pV9XuB5<br>
A Matrix space is also planned but is currently not going to exist as full sync with Discord (with all the previous messages being posted) is not possible yet.

## Contributions
Unlike the original source(s), this version is in stable development so pull requests are absolutely accepted, provided they don't break the engine. Bear in mind though that this version of DNH still relies on mkm's original source code, most of which is either very unoptimized even with optimization flags or very outdated in execution.

## License
zlib library has its own license, please check zlib.h in the repo for that information.</br></br>
This fork is licensed under the MIT license. GPL had been considered, but it was ultimately not chosen to save space due to its somewhat infamous "infectious license" problem. However, the author acknowledges the problems that copyright law brings, and welcomes suggestions to use a better license.
The license text was taken from https://opensource.org/license/mit/.
