# Corewar 👾
The final project of the Algorithm-branch at Hive Helsinki.  

The project consists of three parts:  
- [Virtual Machine](#Virtual-Machine)   
  * The Game itself, a platform for the champions to battle.  
- [Assembler](#Assembler)  
  * Takes the champion's raw information and commands,  
  and transforms it to asssembly language for the Virtual Machine to understand it.  
- [Champion](#Champion)  
  * an AI player in the corewar-game, has a name, comment and commands.  
  
The whole project had to be done according to Hive's Norminette; a set of rules that restrict and improve the way we code.  

We allocated [Pavel](https://github.com/pavel-arkharov) and [Marius](https://github.com/Sickology101) to work on the Assembler, and [Ian](https://github.com/IanGaplichnik) and [Miro](https://github.com/MiroTissari) to work on the Virtual Machine.  
  
  
### Usage
  
Copy the repository git clone it on your terminal:  
 ```git clone https://github.com/Sickology101/Corewar.git```  
At the root of the repository, type ```make``` to compile both programs.  
  
  
<details><summary>Using Assembler</summary>
<p>

To be released soon.

</p>
</details>
  
  
<details><summary>Using Virtual Machine</summary>
<p>

To be released soon.

</p>
</details>
  
  
## Assembler

<details><summary>a section</summary>
<p>

To be released soon.

</p>
</details>
  
  
  
  
## Virtual Machine
<details><summary>Verifying and Validating</summary>
<p>
  
The Virtual Machine starts with parsing and verifying the input.  
While doing so, we also check if there are flags present, and save that information for the printing part.  
There can be 1 - 4 players, the extension has to be _.cor_, and supported flags are -n [nbr] & -dump [nbr].
  
  
Then we read the files one by one, perform various validations and save the data into _s_player_ -struct.  
The validation includes checkin the _Magic Header_, _champion name_, _champion comment_, the _size of the executable code_, and the _executable code_ itself. There are _Null separators_ in between, and the sizes of _Magic Header_, _name_ and _comment_ are prefixed.  
  
| <img style="float:right" width="400" alt="honkyJoe cor" src="https://user-images.githubusercontent.com/90178358/219679483-5511009a-6850-4fe5-a1d2-645d6ccf3ad0.jpeg#right"> | <img width="398" alt="honky_Joe2 cor" src="https://user-images.githubusercontent.com/90178358/219703368-2426bf77-042e-47d7-bf87-07aa369d55cc.jpeg#right">
|:--:|:--:|
|<em>at the beginning of the .cor -file</em>|<em>at the end of the file</em>|
</p>
</details>
  
  
<details><summary>Game loop</summary>
<p>
  
To be released soon

</p>
</details>
  
  


  
## Champion
  
<img align="right" width="200" alt="JoeTheChamp" src="https://user-images.githubusercontent.com/90178358/219705436-d2724a41-c64e-4725-a2aa-780cd7087f5d.jpeg#right">

The Champion didn't need to be a good one for this project, just one that works and stays alive for a while.  
  
After completing the Assembler and Virtual Machine it wasn't too hard to make the champion,  
as the moves were familiar.
  
We didn't feel the need to make a good fighter, but an easygoing fellow who goes by the name Honky Joe.  

Honky Joe was born in Louisiana and Hungary, and the doctors knew from the beginning he was going to be honky.  
Without any hand-eye coordination, Joe often slaps people by accident.  
But because Joe is such a nice fellow, he let's the other champions beat his a**, 
hence Honky-Joe is not the greatest of fighters.  
  
He is the honkiest.
  
  
  
  
  
