
# Quake 2: Window of Retaliation, The Armageddon Device, The Earth War - KMQuake 2 port.

## Description
I always loved the add-ons from these authors and always wanted to replay them on an engine with improved graphics (for example, on KMQuake 2), but the authors did not publish the source codes of their mods, so I took the liberty of recreating the content contained in gamex86.dll from scratch (namely weapons, monsters and some scripts). More than a week of hard work - and the result was an almost complete copy (except for some differences, which will be described below).

## About the port
Since the source code for these mods are not publicly available online, I had to do everything myself. I was not familiar with C++ before, so it was very difficult, but the Quake 2 game.dll manuals helped. I calculated the monsters' stats (damage, health, etc.) "by eye", for example, the number of blaster shots to knock down a shield and etc. I marked all the new code with my name (petunindan) to make it easier to find new lines if you want to fix something or just curious. I used the latest version of Visual Studio for compilation in June 2021. In total, it took more than a week to write all this. I sincerely hope that the original authors will not be offended by all this copying without permission. A general description of the new code and the main differences from the original mod can be found below.

I adapted the mod's resources for KMQuake 2 - I drew icons of new weapons and items. I have not tested the multiplayer. All new materials are packed in .pk3, so that the old version for the regular Quake 2 does not load them. The code of add-ons was taken as a basis, which also introduced a new, smarter AI than in the original.
Since I did not find a way to assign several weapons to one key, I decided to assign new weapons to other buttons. By default:
V - contact grenade. Or the command "bind V use proximity grenades".
N - feedback laser. Or the command "bind N use feedback laser".
M - plasma gun. "bind M use plasma gun".

## Original mod description

**Window Of Retaliation** - is a Quake 2 addon containing 9 levels.  
The action takes place after the defeat of Macron. You play the role of a pilot, carrying out a "search and destroy" mission, cleaning out the remnants of the Strogg forces.  
While carrying out a routine mission, you are shot down on a remote planet belonging to the Strogg, and discover that they are planning a revenge strike. You must unravel the nature of this strike and stop it before the Earth is destroyed.  
Window of Retaliation introduces new weapons and monsters to the standard Quake 2 set.

**The Armageddon Device** is an addon for Quake 2, containing 8 levels.  
An asteroid the size of half a moon is heading towards Earth. When it hits, all life on Earth will be destroyed. This is no ordinary piece of planetary debris. This rock has a primitive thermonuclear drive and the most powerful shield we have ever seen. This weapon is the Strogg's last hope for victory, codenamed "The Armageddon Device".  
This information was obtained when a ship from Earth intercepted a Strogg shuttle en route to the asteroid.  
The shield is generated and controlled from a reactor on the rock itself. None of the Strogg know the deactivation code. There are three Strogg commanders, each of whom knows two digits of the six-digit code. We do not expect them to tell us them willingly.

You play as an elite marine with the task of obtaining the deactivation codes for the device.  
Action Plan:  
1) You will be transported to the asteroid's estimated launch location. There is a class M planet in that area, and we expect to find a Strogg colony there.  
2) Your captain will scan the area to find a suitable place for a stealthy landing.  
3) You will lead a team of 4 and attempt to obtain the deactivation code from the Strogg commanders. Your battle computer has been adapted to read the Strogg cerebral implants and extract the code. This cannot be done while the implant's owner is alive.  
4) Once you find the code, you will need to find a way to get to the asteroid and disable the shield.  
5) Our warship will destroy the rock with thermonuclear charges.  
Good luck, soldier!

**The Earth War** is an addon for The Armageddon Device, containing 9 new levels. The missions, created by Forrest "Gumpsta" Glithero, take place on earth during the Strogg invasion. Exciting action, enemies and weapons from previous add-ons. To launch this add-on, launch "The Armageddon Device", start a new game and select the difficulty. After loading the game, open the console and write "map park", this command will take you to the beginning of the campaign "The Earth War".

## Weapons

### Air Force Blaster
Pilots are issued a slightly more powerful version of the standard blaster. Fires two bolts per shot in rapid succession.  

### Feedback Laser
An amazing weapon. Uses a modified railgun system to charge a powerful laser, but for even more power, the user can feed the outgoing pulse directly through the charging chamber's feedback. The charge continues until the trigger is released, releasing a powerful beam that destroys everything in its path.  
A visible meter shows the charge level as a percentage.  
A 100% charge is roughly comparable in power to a BFG.  
Caution! Exceeding 102% charge overloads the weapon, which can cause a large explosion! You have been warned, soldier!  
The weapon has no area of ​​effect, but is highly accurate and fast, but requires the shooter to aim accurately and control the charge.

### Plasma Cannon
This weapon fires superheated gas charges in automatic mode. The charges have a small area of ​​effect and are very effective in automatic fire.
Thanks to the Loki's Missions team for kindly allowing us to use their plasma cannon model.  

### Contact Grenades
Available only for throwing and cannot be used with the grenade launcher. They are triggered when an enemy is nearby. Contact grenades can be distinguished from regular grenades by a yellow marking strip.

## Monsters

### Storm Trooper
He is an elite guard of the Strogg forces of vengeance. Armed with a powerful shield and a machine gun, he can be a serious opponent.

### Hornet Class Flyer
An experimental modification of the monster "Flyer". Strogg tried to install a railgun and a shield generator on a frame that was already overloaded.  
Deadly in surprise attacks, especially when hidden in a swarm of regular Flyers. He has one drawback: the generator that powers the shield cannot be properly cooled on such a large frame. Overload it - and it will explode. The resulting sparking and smoking hornet becomes an easy target.

### Proxy Parasite
A parasite with a habit of throwing contact mines. Watch where you step!

### Traitors
People who have defected to the Strogg. They carry machine guns and tend to stick together in groups.

### Laser Gladiator
A deadly foe. Heavily armored, fast, and armed with a feedback laser. Beware!

### Tank General
The top of the tank hierarchy. These guys are slow, but well armed and armored. They are especially problematic in groups!

### Death Tank
Faster and more aggressive than their brethren. Armed with a plasma cannon and a pulse laser, they will not give you any room for mistake! Easily recognizable by the skull and crossbones sign.

### Hyper Tank
The final boss. Armed with rockets, grenades, a blaster, and a machine gun, they use a BFG if things get really bad.

### Boss-Traitor
There were problems with using human DNA - the clones were too cunning and rose to the top of the Strogg hierarchy, seizing power. He is also a scientific genius, using Strogg technology to its full potential. He uses a personal cloaking device as well as a whole arsenal of weapons.

## The main differences between the KMQ2 port and the original mod ***
Air Force Blaster - no different from the original.  
Feedback Laser - identical to the original except that the original authors managed to untie the firing mechanics from the weapon model animation, I couldn't do it and had to change the weapon model to the new code.  
Plasma Cannon - identical to the original + ammunition.  
Hyper Blaster - just like in TaD, it fires a green tracer every few shots.  
Contact Grenades - the original used regular grenades, but the clockwork was replaced with the logic: "The enemy approaches - the mine explodes, allies approaches - the mine doesn't explode." I tried to do this too, but it didn't work, so I used the logic of proxy grenades from the "Ground Zero" add-on.  
Assault Soldier - identical to the original.  
Hornet Class Flyer - identical to the original.  
Proxy Parasite - the original one threws proxy mines next to itself. Due to the change in the logic of the proxy grenades, now it throws a mine towards the player, but the "grenade" flag allows monsters to bypass their mines and not step on them.  
Traitors - identical to the originals, except for some minor differences. And yes, my code for them is a garbage, please don't laugh :D . But it works! Except that the boss can sometimes forget to turn on / off the shield.  
Laser Gladiator - identical to the original.  
Tank General - identical to the original.  
Death Tank - identical to the original.  
Hyper Tank - identical to the original. The weapon code was spied on in StroggDM.  
In one of the missions there is a task to destroy several monsters, including a tank sitting in a chair. I struggled with this task for a long time, it stubbornly refused to count, but suddenly I added something and it began to count. I didn't understand what I added, but I didn't touch it and closed the map file without breathing.  
DNA Scanner - The only thing I couldn't do. There are "trigger_dna" on the map and they are activated only when the player has "DNA Scanner" in his inventory. No matter how I tried to do it, nothing worked. The main problem was finding the code for checking the player's inventory - there are simply no examples, and all attempts to write something myself caused the game to crash. Therefore, I had to make it so that the triggers were activated without a scanner.  
The final riddle with numbers is a tough nut to crack, but I cracked it, unlike the previous one. As I understand it, in the original, the developers used some kind of system involving a trigger, but I did it my way, and it seems to work.

*** Authors ***
Mod developers - Roseville Missions Team. Webarchive link: https://web.archive.org/web/20210927070110/https://www.quakewiki.net/archives/roseville/  
Adaptation for KMQuake2 - Petunindan  
All original documentation for mods is in the “rose_docs” folder.

