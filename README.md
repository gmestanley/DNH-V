Description coming soon.

## Requirements (for compiling)
 * zlib
</br>Best and recommended way to obtain it is to use [vcpkg](https://github.com/Microsoft/vcpkg) C++ Library Manager.
 * sfml
</br>Get it here: https://sfml-dev.org
</br>Also deserves credit because it was used to implement netplay in the first place.

## Known Issues
 * Wine 4.12.1 (confirmed on macOS at least) suffers some scaling problems with the window size, being 9 pixels too wide and 7 pixels too tall.  This causes some nasty scaling on in-game assets, possibly a result of old Windows size calls not being 100% compatible with Wine releases.
 * The exe will crash when trying to load a sound file that is both: not 1411kbs and is stereo (fixed in Woo; fix will be brought over soon)

## Special Thanks
WishMakers - for making Danmakufu Woo and helping me out

## Contributions
Unlike the original source(s), this version is in active development so pull requests are absolutely accepted, provided they don't break the engine. Bear in mind though that this version of DNH still relies on mkm's original source code, most of which is either very unoptimized even with optimization flags or very outdated in execution.

## License
zlib library has its own license, please check zlib.h in the repo for that information.</br></br>
(quoted from James7132's repo of the original source, maintaining the same license.) </br>This code is licensed under the NYSL (Niru nari Yaku nari Suki ni shiro License'). Main translated points:

 * "No warranty" disclaimer is explicitly included.
 * Modified version of the software MUST be distributed under the responsibility of the distributer.
 * Official version is written in Japanese.
