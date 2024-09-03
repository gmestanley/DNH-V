# Touhou Danmakufū V
A modified version of Danmakufu ph3.5 "Woo" aiming to provide better functionality to the engine, such as general improvements and others including new features, like Netplay.<br>
All documents have been translated from Japanese to English by me.<br>
Crossplatform support is also planned for GNU (Hurd, Linux-libre), PE-running systems like Windows, and Mach-O-running systems like macOS. The [linux](https://github.com/gmestanley/DNH-V/tree/linux/) branch was a work in progress and set to be used for GNU+Linux or the OS commonly called "Linux", but was soon to be merged with main and is now scrapped, as is support for the variant (users please use Linux-libre version; the ABIs are the same). Currently, only Windows is supported by the engine; this will change.

<abbr style="color:red">* This legacy repository is no longer being maintained. Please check out [the main repository dmf-v](codeberg.org/gmestanley/dmf-v) instead.*</abbr>

## Changelog
Aside from the current releases, there were changes made in older versions; check the older repository [DNH-Netplay](github.com/gmestanley/DNH-Netplay) to see a log of them.

### [0.6.2]
 * Error-catching in the Netplay functions' logging improved
 * LocalNetData renamed to GetLocalNetData
 * Implemented new function SetLocalNetData
    - Sets any data recently saved by ReceiveNetData to a string specified in the first argument.

### [0.6.1]
 * Design updated
 	- Title was changed from "DNH Netplay" to "DNH-V", and further mentions of "Netplay" were also replaced with that.
 * Translations of the Readme and adjacent documents provided (along with the original forms)
 * Example script for Netplay functionality provided (misplaced in script/sample/)
 * VS Projects changed to Visual Studio 2019

## Requirements (for compiling)
 * zlib
 * sfml
<br>Get it here: https://sfml-dev.org
<br>Also deserves credit because it was used to implement netplay in the first place.

## Known Issues
 * Script functions do not work (top priority, is being fixed)
(Originally from Woo)
 * Wine 4.12.1 (confirmed on macOS at least) suffers some scaling problems with the window size, being 9 pixels too wide and 7 pixels too tall.  This causes some nasty scaling on in-game assets, possibly a result of old Windows size calls not being 100% compatible with Wine releases.
 * The engine will crash when trying to load a sound file that is both: not 1411kbs and is stereo (fixed in Woo; fix will be brought over soon -gmestanley)

## Special Thanks
WishMakers - for making Danmakufu Woo and helping me with this project<br>
Mana - provided the fix for ItoA and IntToString's int range

## Contact
This project has a Discord server. If you want to talk about it in there, use this ID on Discord: W93pV9XuB5<br>
A Matrix space is also planned but is currently not going to exist as full sync with Discord (with all the previous messages being posted) is not possible yet.