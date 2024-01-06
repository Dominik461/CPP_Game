This project was a voluntary part of a C++ module I absolvet in my 3rd semester.

It is a turn based game displayed in the console.

You can walk in world with w,a,s,d. The walkable spaces are displayed with '.' while blocked spaces are displaed '@'.
The player is displayed with as 'p' while other letters are enemies. If you collide with an enemy you enter a battle with them.

The playyer has currently 3 actions in battle:
- Pressing 'a' will do a standard attack
- Pressing '1' or '2' will use the respective ability
  - The ability is ready when between every bracket is a plus displayed. An example with an ability which cooldown is 3:
    - "[+] [+] [+]" indicates that the ability is ready
    - "[ ] [ ] [ ]" indicates that the ability is on cooldown
  - each turn the cooldown is reducded, a plus is filled in from left to right until it is ready again

The game ends if all enemies are defeated or the player died
