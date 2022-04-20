# MSense

This project is inspired by the badgersense nosedive indicator, except building it yourself.

# Disclaimer

The authors and contributors of this project are in no way affiliated with Future Motion Inc. or Badgerwheel Inc. 
Onewheel, Onewheel XR, Onewheel Pint, Onewheel Plus, etc are registered trademarks of Future Motion Inc.

This is a hobby projet for its contributors and comes with absolutely no guarantees of any sorts. **Messing with your Onewheel in any way voids its warranty and could potentially lead to property loss, injuries or even death.** Don't be silly and use this project at your own risk.

# Features

  - Displays duty cycle 
  - Displays current speed (to a varying degree of accuracy)

# To Do

  - Make MPH values much more reliable (switching to interrupts probably).
  - add battery voltage readout (will probably need a few more resistors and use of the analog pin).
  - Improve instructions/readme

# Parts list

RGB strip I used: https://www.amazon.com/dp/B09PBHJG6G?psc=1&ref=ppx_yo2ov_dt_b_product_details 
Step down converter: https://www.digikey.com/en/products/detail/recom-power/R-78HB5-0-0-5-W/5765379

You need to use a LED strip with WS2812B LEDs, and a step down converter that will accept the voltage range of 40v - 66v, and step it down to 5v.

## Resistors
I used the following specs:
  - 1x 10k ohm
  - 1x 1k ohm
  - 1x 100k ohm
  - 2x 47k ohm

If you understand how voltage dividers work, build one that will step down 65v to 3.3v, with minimal current loss (hence the high resistance).
The ratio should be around 11/200.

# Instructions

Wire everything up as follows

<img src="docs/img/wiring.png?raw=true" height="400px">