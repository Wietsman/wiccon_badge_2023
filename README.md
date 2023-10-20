# Wiccon Badge 2023

# What is this repo: 
  This repo contains the source + firmware + PCB design for the WICCON 2023 Badge (https://wiccon.nl/)

  The Folder PCB contains the main badge and the addon, created with KiCad.
  # Main badge
  * 4 WS2812B on the front. (made a mistake the are adressed counter clockwise)
  * 1 MODE button on the front to switch LED effects
  * 2 6 pin female connecter to attach the addon board
  * 1 SAO v1.69 (Shitty Addon) (https://hackaday.com/2019/03/20/introducing-the-shitty-add-on-v1-69bis-standard/)
  * |  PIN  |      Description      |
    |-------|-----------------------|
    | 3.3v  | Positive power supply |
    | GND   | Ground                |
    | SCL   | Not connected (sorry) |
    | SDA   | Not connected (sorry) |        
    | GPI12 | General-purpose pin   |
    | GPI13 | General-purpose pin   |    
![alt text](https://github.com/Wietsman/wiccon_badge_2023/blob/master/images/addons-sao-v1_69bis.png?raw=true)
