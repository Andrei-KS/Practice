<h1> Setup </h1>
Created С++ UE5 project from FPS template.

![screen of the content browser](https://github.com/Andrei-KS/Practice/assets/74614116/d3d3c5d2-2772-4a87-a153-e03fe32f2100)

In the framework of this section, the functional and possibility of the created template project were investigated, namely, movement, and shooting in-game, also researched blueprints and C++ files of this template

<h1> Version Control </h1>

![screen of the diff BP](https://github.com/Andrei-KS/Practice/assets/74614116/a97c9cf5-acff-4aaa-90be-1ba427feebc5)

In the framework of this section, created the current repository, and added several blueprints to execute the "blueprint diffs" for various versions of blueprints.

<h1> Basic Classes </h1>

![screen of the content browser](https://github.com/Andrei-KS/Practice/assets/74614116/64628cd6-8854-45d2-a6ef-ca24bd492db1)

Created two C++ classes: AmmoComponent, and Health component.

![screnn of health component graph](https://github.com/Andrei-KS/Practice/assets/74614116/06feed03-8a21-4759-acb0-bab1483ab4a0)

The health component allows adding the possibility of to actor being destroyed if one gets hit by a projectile.

![gun, ammo, and destructible cube](https://github.com/Andrei-KS/Practice/assets/74614116/96cf49cd-636f-4ca3-aaf9-8f45041d5a78)

Added ammo counter to the character actor that doesn't allow shot using a gun if this counter is equal to zero. Also ammo component destroys his actor owner when the character picks up it.
