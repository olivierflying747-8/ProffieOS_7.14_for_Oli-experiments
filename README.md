<p style='text-align: left; font-size:66% '> ProffieOS v6.7x010  </p> 

# **Proffie OSx**

---
## What is it?
ProffieOSx is a customized version of ProffieOS. If you're not familiar with ProffieOS you might want to check the [ProffieOS Documentation](https://pod.hubbe.net/) first. 
Although ProffieOSx relies heavily on ProffieOS, not all the features of OS are compatible with OSx and most of what's documented about OS is obsolete under OSx. This documentation covers mainly the OSx alterations of ProffieOS.
##### OSx Alterations:
- __Runtime configuration__: blades, presets, motion sensitivities... are all defined by files instead of code. This allows remote configuration without the need to rewrite the firmware. Styles are still defined in firmware (for now), so editing the style library still requires a firmware overwrite.
- __On-board Menus__: General purpose ticking and scrolling menu based on twist gestures. The 'Twist & Tick' menus are used by the UltraSaber prop to control preset, color, volume, brightness and master sensitivity.
- __Colorimetric LED Driver__: a full replacement of ProffieOS's PWM driver, allowing colorimetric control of analog LEDs.
- __Power Manager__: 
- __Extended Interface__: 



---
## How to install
1. Prepare the [ProffieOS setup](https://pod.hubbe.net/proffieboard-setup.html).
2. Open Arduino, go to 'Preferences' and add the following Board Manager URL: https://ultraproffie.com/package_ultraproffie_index.json in Board Manager 
3. Go to 'Boards Manager' and install the 'UltraProffie' package.
4. Download the [ProffieOSx source code](../../) and open ProffieOS.ino.
5. Select the appropriate board in Arduino. Make sure that the selected operating system is ProffieOSx.
6. Verify and upload as usual. 
6. Copy the [board files](https://ultraproffie.com/pages/board_files), as well as any sound fonts and tracks you want, to the SD card. If your board is not equipped with an SD card, go to [ultraproffie.com](https://ultraproffie.com/), connect via USB and use 'Restore factory defaults' and 'Write font'.

---
## Getting started
* [Github Wiki](../../wiki)