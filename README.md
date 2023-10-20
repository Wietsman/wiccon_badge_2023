# Wiccon Badge 2023

# What is this repo: 
  This repo contains the source + firmware + PCB design for the WICCON 2023 Badge (https://wiccon.nl/) (not the SAO)

  Badge front:
![Frontside](https://github.com/Wietsman/wiccon_badge_2023/blob/main/images/Badge_Front.png?raw=true)  

  Badge back:
![Backside](https://github.com/Wietsman/wiccon_badge_2023/blob/main/images/Badge_Back.png?raw=true)    


  The Folder PCB contains the main badge and the addon, created with KiCad.
  # Main badge
  ## Frontside
  * 4 WS2812B on the front. (made a mistake they are adressed counter clockwise)
  * 1 MODE button on the front to switch LED effects
  * 2 6 pin female connecter to attach the addon board (Cat and moon)
  * 1 SAO v1.69 (Shitty Addon) (https://hackaday.com/2019/03/20/introducing-the-shitty-add-on-v1-69bis-standard/)
  * |  PIN  |      Description      |
    |-------|-----------------------|
    | 3.3v  | Positive power supply |
    | GND   | Ground                |
    | SCL   | Not connected (sorry) |
    | SDA   | Not connected (sorry) |        
    | GPI12 | General-purpose pin   |
    | GPI13 | General-purpose pin   |    
![SAO v1.69](https://github.com/Wietsman/wiccon_badge_2023/blob/main/images/addons-sao-v1_69bis.png?raw=true)

![back3d](https://github.com/Wietsman/wiccon_badge_2023/blob/main/images/wiccon_2023_badge_front.png?raw=true)

## Backside
* ESP8622
* Powerswitch
* Reset button
* Flash button
* Batterybox
* stepdown converter (3.6-4.5v) to 3.3v
* couple of capacitor for WS2812B and stepdown converter
* 1 resistor
* lots of test pads so you can reuse the badge for other projects

![back3d](https://github.com/Wietsman/wiccon_badge_2023/blob/main/images/wiccon_2023_badge_back.png?raw=true)

## Schematic
![Schematic](https://github.com/Wietsman/wiccon_badge_2023/blob/main/images/wiccon_2023_badge_schematic.png?raw=true)

## Usage
The badge has been designed to be reused for your project. The test pads can be used to solder anything to it and you can flash the ESP. 

You can use all the pads/pins except for (because i orderd the wrong ESP.....):
* MISO
* MOSI
* GPIO09
* GPIO10
* SCLK
* CSO

The following pins need are "special":
* GPIO00 pull to ground on boot to flash the ESP (or press flash button)
* GPIO15 is pulled to ground through a 10k resistor otherwise the ESP wont boot.

Flashing your own firmware, connect UART to tx/rx gnd power the device by battery or external 3.3v power. Hold the flash button, then press reset, release the flash button. Now you can flash your own firmware with esptool.py, arduino ide or what ever you want.



# Addon board
There are 2 addon boards for WICCON 2023, for guests (black cat and moon) and orga (purple moon, silver cat)
## Guestboard
![guest cat](https://github.com/Wietsman/wiccon_badge_2023/blob/main/images/wiccon_2023_badge_addon_guests_front.png?raw=true)
## Orgaboard
![orga cat](https://github.com/Wietsman/wiccon_badge_2023/blob/main/images/wiccon_2023_badge_addon_orga_front.png?raw=true)
## Schematic
![schematic](https://github.com/Wietsman/wiccon_badge_2023/blob/main/images/wiccon_2023_badge_addon_schematic.png?raw=true)

## Backside
![backside](https://github.com/Wietsman/wiccon_badge_2023/blob/main/images/wiccon_2023_badge_addon_orga_back.png?raw=true)


# Questions, remarks or whatever!

If you have any questions please drop me a message: 
* twitter: [twitter](https://twitter.com/wietsman)
* Website: [WBSEC.nl](https://www.wbsec.nl)


