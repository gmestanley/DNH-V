# Touhou Danmakufu ph3.5 0.4 ~ Netplay Edition
This version of Danmakufu is made for implementing Netplay in it; see WishMakers' repository for a link to the original download. <b>The master branch version of this repo is completely backwards compatible with ph3 (and has the original readme). This branch contains functions that are not in original PH3. If something doesn't work as expected, refer to the contact info in Woo (the repo original to this one).</b> Most of the stuff there also applies here.

###### [0.4]
 * Changed ReceiveTCPData
 	- The function now returns saved data instead of nothing, allowing the example script to actually work
 * Added a functional logging system
 	- Functions will write what happens to the WindowLog

###### [0.3]
 * Changed ReceiveTCPData
	- The function now deletes saved data before receiving instead of after
 * Fixed the data saving system
 	- SendTCPData now actually returns saved data instead of nothing

###### [0.2]
 * Changed RunNetplay's first argument to "server", bool
	- Removed UDP support to focus on TCP

###### [0.1]
 * Added RunNetplay(mode, port, address)
	- Runs the Netplay module in TCP server, client or UDP client mode, with the appropriate port and address
 * Added ReceiveTCPData(delete)
	- Receives data from the other person in the connection, deleting the data received or not
 * Added SendTCPData(data, direct)
	- Sends data to the other person in the connection, either custom or directly any saved data

## Requirements (for compiling)
 * zlib
</br>Best and recommended way to obtain it is to use [vcpkg](https://github.com/Microsoft/vcpkg) C++ Library Manager.
 * sfml
</br>Get it here: https://sfml-dev.org
</br>Also deserves credit because it was used to implement netplay in the first place.

## Known Issues
 * Wine 4.12.1 (confirmed on macOS at least) suffers some scaling problems with the window size, being 9 pixels too wide and 7 pixels too tall.  This causes some nasty scaling on in-game assets, possibly a result of old Windows size calls not being 100% compatible with Wine releases.
 * The exe will crash when trying to load a sound file that is both: not 1411kbs and is stereo

## Special Thanks
WishMakers - for making Danmakufu Woo and helping me out

## Contributions
Unlike the original source(s), this version is in the border of active and inactive development so pull requests are absolutely accepted, provided they don't break the game. Though bear in mind that this version of DNH still relies on mkm's original source code, most of which is either very unoptimized even with optimization flags or is very outdated in execution.

## License
zlib library has its own license, please check zlib.h in the repo for that information.</br></br>
(quoted from James7132's repo of the original source, maintaining the same license.) </br>This code is licensed under the NYSL (Niru nari Yaku nari Suki ni shiro License'). Main translated points:

 * "No warranty" disclaimer is explicitly included.
 * Modified version of the software MUST be distributed under the responsibility of the distributer.
 * Official version is written in Japanese.
