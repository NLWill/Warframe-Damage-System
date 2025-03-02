# Warframe Damage System

This is a project to re-create the complex damage system from the game Warframe. 

Throughout this project, I seek to  simulate the entire system to accurately predict behaviour in prescribed circumstances.

This project also is inspired by the updates (or lack thereof) for the website Overframe.gg, which frequently takes months or years to add a feature from the game. This system provides functionality such as incarnon evolutions which are still not on Overframe (as of 21st Feb 2025), despite being in Warframe since April 2022. Similarly, an important effect in damage calculations is elemental quantisation, which Overframe does not account for, causing all weapons to have incorrect damage predictions by up to 10%.

This project is currently limited to single-target damage calculations, and it is assumed that all instances of damage hit, so it is likely to overestimate the damage of weapons with radial damage falloff.

Another feature of this simulator is the recognition of status effects and the significant proportion of the total damage that a weapon may deal. Once again this feature is not present on Overframe or any other damage calculator I have found online.
The only status effects not handled yet are the damage-boosting/stat-boosting status effects (e.g. Viral, Magnetic, Corrosive, Cold, Puncture, Tau). This is a limitation of the current system, though I hope to include it as a feature down the line.

As the project stands, Weapons and Mod data must be constructed manually, though I hope to develop a data-based approach to this later down the line. This would allow straightforward commands, such as Equip("Mk1-Braton") or weapon.AddMod("Serration") and the 
function would load the necessary data for the call by itself.