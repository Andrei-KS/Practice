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

<h1> UI </h1>
Added a simple HUD that contains an ammo counter.

![ammo counter](https://github.com/Andrei-KS/Practice/assets/74614116/cad7978f-da32-4519-90e0-42bb004df606)

Added a simple pause menu.

![pause menu](https://github.com/Andrei-KS/Practice/assets/74614116/75ee7f27-de5e-453c-b49f-61d54dba16b3)

Blueprints were used only for design, the whole logic is contained in cpp part

<h1> Input </h1>
Added input action and input mapping context to implentate logic throwing grenade

![input action](https://github.com/user-attachments/assets/77207fc0-dc0d-47a8-b3f2-a5e5d6dc8629)

![input mapping context](https://github.com/user-attachments/assets/cdd0d67a-278a-452e-b9ce-0ba04eafa57e)

<h1> Basic Game Mechanic </h1>
Added logic to display the thrown grenade path and sphere of the its detonation

![thrown grenade](https://github.com/user-attachments/assets/ef02ae97-380b-4282-8826-da8a32d76d37)

![detonated grenade](https://github.com/user-attachments/assets/fc6a70f3-2521-4c8f-8471-c2c223b1ca02)

also added logic that blocks the the grenade detonation shockwave
![wall blocked the damage by grenade](https://github.com/user-attachments/assets/6c8d83f1-546b-490f-928c-3d607d944a5a)

![the box destroyed by grenade](https://github.com/user-attachments/assets/16903d0a-dc6e-4dc6-9c72-c26f9e7bc134)

<h1> Blueprint Virtual Machine </h1>

To get practical knowledge about how BVM (Blueprint Virtual Machine) works I read these two articles ([Anatomy of the Unreal 4 blueprint virtual machine](https://ikrima.dev/ue4guide/engine-programming/blueprints/bp-virtualmachine-overview/), [Discovering Blueprint VM (Part 2)](https://intaxwashere.github.io/blueprint-part-two/)), create simple node as described in articles and got acquainted code base of engine

![{A969DFA5-8549-4E7F-BC61-0F4BE47B6E12}](https://github.com/user-attachments/assets/c4081a91-0748-4246-b5b2-41f78bc70993)

<h1> Working With Blueprint </h1>

Created two version dynamic stairs to get more experience of working with blueprints. Namely, i got more knowledge of working with geometric scripts
GS_StaircaseV1:
![{112E7719-2FBF-446E-86E9-D6628DF112EA}](https://github.com/user-attachments/assets/3d4cc140-b353-4c22-bddf-46ccd4dc5568)
![{37667969-211E-48F6-82C8-0D290B903548}](https://github.com/user-attachments/assets/4de2b1a7-a280-470d-b760-59d9a32cc83c)
GS_StaircaseV2
![{417C91EB-2E3D-41B6-BABE-5D6CCF31B69D}](https://github.com/user-attachments/assets/9c158174-6290-4d06-a18e-275fad60e595)
![{C73AC896-9FAF-4F0D-85CA-E0D5B673E41B}](https://github.com/user-attachments/assets/c739a459-ba57-4a00-a4ae-6a601c36456f)
![{ABE5F0AD-AE38-4826-BB4F-D88B10BD3C89}](https://github.com/user-attachments/assets/447ad99a-5e5a-4869-ac24-452e182c4a22)

<h1> Config and Debug console </h1>

Added Config Variables: bIsLevitationComponentEnabled and LevitationHeightOfLevitationComponent.

Added a Levitation Component to demonstrate the use of these config variables.
The bIsLevitationComponentEnabled variable allows enabling or disabling the levitation component.
The LevitationHeightOfLevitationComponent sets the maximum height that the actor containing this component can reach.

**Note**: The levitation component attempts to find a mesh component within the actor. If a mesh is found, the component applies a force to it.
<img width="701" height="384" alt="{8FAC6CBF-340C-422D-827E-6710846A3ADF}" src="https://github.com/user-attachments/assets/7146bacc-fd06-4db5-9397-3d2272221e17" />
where bIsLevitationComponentEnabled = 0
<img width="683" height="372" alt="{38843228-D543-4A83-9800-66736928600C}" src="https://github.com/user-attachments/assets/e68ef453-68dc-4cf9-b9b1-9d605df7e5a2" />
where bIsLevitationComponentEnabled = 1






