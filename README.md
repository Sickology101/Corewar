# Corewar 👾
The final project of the Algorithm-branch at Hive Helsinki.  

The project consists of three parts:  
- [Virtual Machine](#Virtual-Machine)   
  * The Game itself, a platform for the champions to battle.  
- [Assembler](#Assembler)  
  * Takes the champion's raw information and commands,  
  and transforms it to asssembly language for the Virtual Machine to understand it.  
- The Champion  
  * an AI player in the corewar-game, has a name, comment and commands.  
  
The whole project had to be done according to Hive's Norminette; a set of rules that restrict and improve the way we code.  

We allocated [Pavel](https://github.com/pavel-arkharov) and [Marius](https://github.com/Sickology101) to work on the Assembler, and [Ian](https://github.com/IanGaplichnik) and [Miro](https://github.com/MiroTissari) to work on the Virtual Machine.  
  
  
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


</p>
</details>
  
  
<details><summary>Game loop</summary>
<p>
  
To be released soon

</p>
</details>
  
  
  
  
## Champion
  
The Champion didn't need to be a good one for this project, just one that works and stays alive for a while.
  
  
  
  
  
