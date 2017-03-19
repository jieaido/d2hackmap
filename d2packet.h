
/*
S->C
0x60
The server will send you this packet when a teleport comes into your range of view
60 03 05 XX XX XX XX
(BYTE) Teleport's State
(BYTE) Area ID (where the TP can take you)
(DWORD) Teleport's ID (your side)

Teleport State's
0x00 = This teleport goes to a town area 
0x03 = This teleport goes to a out of town area
0x05 = This teleport goes to a town area and you have used it before
0x07 = This teleport goes to a out of town area and you have used it before

*/




/*

S->C
0x5A - Player infomation messages
Multiple Packet Types:
D2GS_PLAYERINFOUPDATE
Packet Type 0x00, 0x02, 0x03
Lengh = 40

5A 00 04 00 00 00 00 00 (Char Name) 00 (Acc Name) 00 
(BYTE) Packet Type (0x00, 0x02 or 0x03)
(BYTE) Action Type <- only seen 0x04 for these
(DWORD) Unknown(0)
(BYTE) Unknown(0)
(NULLSTRAND[16]) Char Name
(NULLSTRAND[16]) Account Name

NULLSTRAND[16] means it is a strand of 16 null bytes with the string its self in side.
Packet Type's:
0x00 = Player Has Dropped Due To Time Out
0x02 = Player Has Joined The Game
0x03 = Player Has Left The Game


Packet Type 0x04
Player Is Not In The Game <- answer from @wisper command
Lengh = 40

5A 04 00 00 00 00 00 00 (Char Name) 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
(BYTE) Packet Type (0x04)
(BYTE) Action Type - 0x00
(DWORD) Unknown(0)
(BYTE) Unknown(0)
(NULLSTRAND[16]) Char Name (That ws not logged into the game)
(NULLSTRAND[16]) Blank

The server will send you this packet after you have used the @charname command to wisper a player that is not in the game.


Packet Type 0x06
Player Has Been Slained
Lengh = 40

5A 06 04 13 00 00 00 01 (Dead Char Name) 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
5A 06 04 02 00 00 00 00 (Dead Char Name) 00 (Killed By Char Name) 00
(BYTE) Packet Type (0x06)
(BYTE) Action Type -0x04
(DWORD) Monster Type (That slained the player)
(BYTE) Player Type (That slained the player)
(NULLSTRAND[16]) Char Name (That was slained)
(NULLSTRAND[16]) Slainer Char Name (That Slained the player)

The server will send you this packet to notify you if your/another player has been killed.
After this packet you will recv a 0x8E packet to asign there player ID to a corpse ID.
If the player type is 01 (monster) or 02 (object) then the slainer charname will be blank and the monster type DWORD will be the ID code of the monster/object, where as if player type is 00 (player) the slainer charname will contain the charname of the player that slained the now dead player and the monster type DWORD will be the char type that slained the player.
NULLSTRAND[16] means it is a strand of 16 null bytes with the string its self in side.
Player Type's:
0x00 = Amazon
0x01 = Sorceress
0x02 = Necromancer
0x03 = Paladin
0x04 = Barbarian
0x05 = Druid
0x06 = Assassin


Packet Type 0x07
Player To Player Relations
Lengh = 40

5A 07 02 1B B1 2E 14 05 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
(BYTE) Packet Type (0x07)
(BYTE) Action Type
(DWORD) Players ID
(BYTE) Player's Action
(NULLSTRAND[16]) Blank
(NULLSTRAND[16]) Blank

The server will send you this packet to notify you of any changes that a D2 client would use to set up partys/hostile players/looting etc.
This packet is a very important packet when it comes to party relations and should be the packet you take note of when adding party support into your bot.
Action Type 0x00 - Nutural
Player's Actions:
0x04 = Player has removed Hostile

Action Type 0x02 - teaming
Player's Actions:
0x05 = Player Is Asking To Party With You
0x07 = New Player Has Joined Party
0x08 = Your Now In This Players party?

Action Type 0x04 - friendly
Player's Actions:
0x02 = Player has given you loot

Action Type 0x08 - nasty
Player's Actions:
0x03 = Player has gone hostile

Action Type 0x09 - remove
Player's Actions:
0x09 = Player has left your party
0x06 = Player has removed party invite
0x0B = Player has removed Loot






*/



/*
S->C
0x5B
D2GS_PLAYERINGAME 
Lengh = 36

5B 24 00 XX XX XX XX 01 (Char Name) 00 01 00 FF FF 00 00 00 00 00 00 00 00
(WORD) Packet Lengh
(DWORD) Player's ID
(BYTE) Char Type
(NULLSTRAND[16]) Char Name
(WORD) Players Char Level
(WORD) Players Party Number (0xFFFF = none)
(VOID) Null-Padding

The server will send you this packet to notify you that a player is in the game and will only send you this packet once for each player present in the game.
This packet will also be sent to you when another player has joined the game as wall as being followed by a 0x5A packet type 0x02 for notification.
NULLSTRAND[16] means it is a strand of 16 null bytes with the nullstring its self in side.
(This is the packet to asign a player to there player ID)
Char Types
0x00 = Amazon
0x01 = Sorceress
0x02 = Necromancer
0x03 = Paladin
0x04 = Barbarian
0x05 = Druid
0x06 = Assassin

C->S
0x5E
Party Request's

5E 08 3E 82 EB 2B 
(BYTE) Action type
(DWORD) Player ID (Of The Other Persion)

Action Type's
0x06 = Invite A Player To Party With You
0x07 = Cancel A Party Invite To Another Player
0x08 = Accept A Party Invite From Another Player

C->S
0x5D
Set Player Relations

5D 01 01 DC A0 9F D7 
(BYTE) Request ID
(BYTE) Action Types
(DWORD) Player ID (Of The Other Persion)

Request ID 0x01
Action Type's
0x00 = Remove This Players Rights To Loot Your Corpse
0x01 = Allow This Player To Loot Your Corpse

Request ID 0x02
Action Type's
0x00 = Allow This Player To Hear You
0x01 = Stop This Player From Hearing You

Request ID 0x03
Action Type's
0x00 = Unsquelch This Player
0x01 = Squelch This Player
(You must also send 0x0E /squelch there username to BNCS)

Request ID 0x04
Action Type's
0x00 = Remove Hostile With This Player
0x01 = Go Hostile With This Player


*/

/*
C->S
0x26
Drink A Potion From Your Belt

26 99 9B 1C 5E 00 00 00 00 00 00 00 00 
(DWORD) Potion's ID
(DWORD) Unknown(0)
(DWORD) Unknown(0)

Send this packet to drink a potion from your belt.

*/


/*
C->S
0x0D
Right Skill On Object

0D 01 00 00 00 6C B0 40 96 
(DWORD) Object Type
(DWORD) Object ID

When sending this packet to attack somthing, your char will use its current selected right skill.
This will cover both melee attacking skills and missle casting skills.
Object Type's
0x00 = Right Attack another player
0x01 = Right Attack a Monster
0x02 = Right Attack An Object (tp, wp, stash, shrines etc)

*/

/*

void __fastcall GamePacketReceivedIntercept(BYTE* aPacket, DWORD aLength)
{
	return;
}
//////////////////////////////////////////////////////////////////////
// GamePacketReceivedSTUB()
// -------------------------------------------------------------------

// before call orignal code
// bl = packet number
// esi = length
// edi = pointer to packet
// free register before pushad: eax
//////////////////////////////////////////////////////////////////////
void __declspec(naked) GamePacketReceivedInterceptPatch_ASM()
{
	__asm {
		mov eax, esi; // save length

		// original code
		movzx esi, bl;
		mov ebp, esi
		shl ebp, 1
		add ebp, esi
		pushad;
		// Call our clean c function
		mov edx, eax;
		mov ecx, edi;
		call GamePacketReceivedIntercept;
		// Return to game
		popad;
		add dword ptr[esp], 1; 
		ret;
	}
}


*/









/*
S -> C

Number   Size   Effect:            Usage: 
---------------------------------------------------------------------------- 
00   1   Game Loading      00 
01   8   Game Flags      01 [BYTE Difficulty] [WORD Unknown] [WORD  Hardcore?] [BYTE Expansion] [BYTE Ladder] 
02   1   Load Successful      02 
03   12  Load Act      03 [BYTE Act] [DWORD Map ID] [WORD Area  Id] [DWORD Unknown] 
04   1   Load Complete      04 
05   1   Unload Complete   05 
06   1   Game Exit Sucessful   06 
07   6   Map Reveal      07 [WORD Tile X] [WORD Tile Y] [BYTE Area Id]    
08   6   Map Hide      08 [WORD Tile X] [WORD Tile Y] [BYTE Area Id] 
09   12   Assign Lvl Warp (Door)   09 [BYTE Unit Type] [DWORD Unit Id] [WORD X] [WORD Y] [WORD Warp Id] 
0a   6   Remove Object      0a [BYTE Unit Type] [DWORD Unit Id] 
0b   6   Game Handshake   0b [BYTE Unit Type] [DWORD Unit Id] 
0c   9   NPC Hit         0c [BYTE Unit Type] [DWORD Unit Id] [WORD  Animation Id] [BYTE Life] 
0d   13   Player Stop      0d [BYTE Unit Type] [DWORD Unit Id] [BYTE  Unknown] [WORD Unit X] [WORD Unit Y] [BYTE Unknown] [BYTE Life] 
0e   12   Object State      0e [BYTE Unit Type] [DWORD Unit Id] [BYTE  Unknown (0x03)] [BYTE 0x00 = Can't Change Back || 0x01 = Can Change Back] [DWORD  Unit State] 
0f   16   Player Move      0f [BYTE Unit Type] [DWORD Unit Id] [BYTE  0x01 = Walk || 0x23 = Run || 0x20 = Knockback] [WORD Target X] [WORD Target Y] 00  [WORD Current X] [WORD Current Y] 
10   16   Player To Target   10 [BYTE Unit Type] [DWORD Unit Id] [BYTE  0x02 = Walk || 0x24 = Run] [BYTE Target Type] [DWORD Target Id] [WORD Current X]  [WORD Current Y] 
11   8   Report Kill      11 [BYTE Unit Type] [DWORD Unit Id] [WORD  Unknown] 
12   26   <Unknown>         ---------- 
13   14   <Unknown>         ---------- 
14   18   <Unknown>         ---------- 
15   11   Reassign Player   15 [BYTE Unit Type] [DWORD Unit Id] [WORD  X] [WORD Y] [BYTE 0x01 = True || 0x00 = False] 
16   *   <Unknown>         ---------- 
17   -    <Unused>         ---------- 
18   15   <Unknown>         ---------- 
19   2   (BYTE)Gold to Inv.   19 [BYTE Amount] 
1a   2   (BYTE)Add Exp.      1a [BYTE Amount] 
1b   3   (WORD)Add Exp.   1b [WORD Amount]    
1c   5   (DWORD)Add Exp.   1c [DWORD Amount] 
1d   3   (BYTE)Base Attribute   1d [BYTE Attribute] [BYTE Amount] 
1e   4   (WORD)Base Attribute   1e [BYTE Attribute] [WORD Amount] 
1f   6   (DWORD)Base Attribute   1f [BYTE Attribute] [DWORD Amount] 
20   10   Attribute Update   20 [DWORD Unit Id] [BYTE Attribute] [DWORD  Amount] 
21   12   Update Item Oskill  21 [WORD Unknown] [DWORD Unit Id] [WORD Skill] [BYTE Base Level] [BYTE Bonus Amount] [BYTE Unknown] 
22   12   Update Item Skill   22 [WORD Unknown (Unit Type?)] [DWORD Unit Id] [WORD Skill] [BYTE Amount] [WORD Unknown] 
23   13   Set Skill      23 [BYTE Unit Type] [DWORD Unit Id] [Byte 0x00  = Right || Byte 0x01 = Left] [WORD Skill] FF FF FF FF 
24   90   <Unknown>         ---------- 
25   90   <Unknown>         ---------- 
26   *   Game Chat      26 [WORD Chat Kind] [WORD Unknown (0x02)]  00 00 00 00 [BYTE 0x05 = Normal Chat || 0x01 = Whisper] [Char Name] 00 [Message] 00 
26 05   *   Overhead      26 05 00 00 [BYTE Unit Type] [DWORD Unit Id]  [WORD Unknown] 00 [Message] 00 
27   40   NPC Info      27 [BYTE Unit Type] [DWORD Unit Id]  [BYTES[34] Unknown] 
28   103   Quest Info      <Research Incomplete> 
29   97   Game Quest Info   <Research Incomplete> 
2a   15   NPC Transaction   2a [BYTE Trade Type] [BYTE Result? - 0x00 =  Purchased || 0x01 = Sold || 0x0c = Insuffecient Gold] [DWORD Unknown] [DWORD  Merchandise Id] [DWORD Gold in Inventory] 
2b   -   <Unused>         ----------    
2c   8   Play Sound      2c [BYTE Unit Type] [DWORD Unit Id] [WORD  Sound] 
2d   -   <Unused>      ----------    
2e   -   <Unused>      ---------- 
2f   -   <Unused>           ---------- 
30   -   <Unused>      ---------- 
31   -   <Unused>           ---------- 
32   -   <Unused>      ---------- 
33   -   <Unused>           ---------- 
34   -   <Unused>           ---------- 
35   -   <Unused>      ---------- 
36   -   <Unused>      ---------- 
37   -   <Unused>      ---------- 
38   -   <Unused>      ---------- 
39   -   <Unused>      ---------- 
3a   -   <Unused>      ---------- 
3b   -   <Unused>      ---------- 
3c   -   <Unused>      ---------- 
3d   -   <Unused>       ---------- 
3e   *   Update Item Stats   <Research Incomplete> 
3f   8   Use Stackable Item   ---------- 
40   13   <Unknown>      ---------- 
41   -   <Unused>      ---------- 
42   6   Clear Cursor      42 [BYTE Unit Type] [DWORD Player Id] 
43   -   <Unused>      ---------- 
44   -   <Unused>      ---------- 
45   13   <Unknown>      ---------- 
46   -   <Unused>      ---------- 
47   11   Relator 1      47 [WORD Param 1] [DWORD Unit Id] [DWORD  Param 2] 
48   11   Relator 2      48 [WORD Param 1] [DWORD Unit Id] [DWORD  Param 2] 
49   -   <Unused>      ---------- 
4a   -   <Unused>      ---------- 
4b   -   <Unused>      ---------- 
4c   16   Unit Skill on Target   4c [BYTE Unit Type] [DWORD Unit Id] [WORD  Skill] [BYTE Unknown] [BYTE Unknown] [DWORD Target Id] 00 00 
4d   17   Unit Cast Skill      4d [BYTE Unit Type] [DWORD Unit Id] [DWORD  Skill] [BYTE Unknown] [WORD X] [WORD Y] 00 00 
4e   7   Merc For Hire      4e [WORD Merc Id?] [DWORD Unknown] 
4f   1   Start Merc List      4f 
50   15   -----         <Needs Research> 
51   14   Assign Object      51 [BYTE Object Type] [DWORD Object Id]  [WORD Object Code] [WORD X] [WORD Y] [BYTE State] [BYTE Interaction Type] 
52   42   Quest Log Info      <Research Incomplete> 
53   10   Player Slot Refresh   53 [DWORD Slot #] [BYTE Unknown 0x00 || 0x80]  [DWORD Tickcount?] 
54   10   <Unknown>      ---------- 
55   3   <Unknown>      ---------- 
56   -   <Unused>      ---------- 
57   -   <Unused>      ---------- 
58   14   <Unknown>      ---------- 
59   26   Assign Player      59 [DWORD Unit Id] [BYTE Char Type]  [NULLSTRING[16] Char Name] [WORD X] [WORD Y] 
5a   40   Event Messages      * 
5b   36   Player In Game      5b [WORD Packet Length] [DWORD Player Id] [BYTE Char Type] [NULLSTRING[16] Char Name] [WORD Char Lvl] [WORD Party Id] 00 00 00 00 00 00 00 00 
5c   5   Player Left Game   5c [DWORD Player Id] 
5d   5   Quest Item State   5d [BYTE Unknown (Id?)]  [DWORD State?] 
5e   38   <Unknown>      ---------- 
5f   5   <Unknown>         ---------- 
60   7   Townportal State      60 [BYTE State] [BYTE Area Id] [DWORD Unit Id] 
61   2   <Unknown>         61 [BYTE Unknown] 
62   7   <Unknown>      ---------- 
63   *   Waypoint Menu      63 [DWORD Unit Id] [BYTES* Available Waypoints] 
64   -  <Unused>      ---------- 
65   7   Player Kill Count      65 [DWORD Player Id] [DWORD Count] 
66   7   <Unknown>      ---------- 
67   16   NPC Move      67 [DWORD Unit Id] [BYTE 0x01 = Walk || 0x17 = Run] [WORD X] [WORD Y] [WORD Unknown] [BYTE Unknown] [WORD Unknown] [BYTE Unknown] 
68   21   NPC Move to Target   68 [DWORD Unit Id] [BYTE 0x00 = Walk || 0x18 = Run] [WORD X] [WORD Y] [BYTE Target Unit Type] [DWORD Target Id] [WORD Unknown] [BYTE Unknown] [WORD Unknown] [BYTE Unknown] 
69   12   NPC State      69 [DWORD Unit Id] [BYTE State] [WORD X] [WORD Y] [BYTE Unit Life] [BYTE Unknown] 
6a   12   <Unknown>         ---------- 
6b   16   NPC Action      6b [DWORD Unit Id] [BYTE Action] 00 00 00 00 00 00 [WORD X] [WORD Y] 
6c   16   NPC Attack      6c [DWORD Unit Id] [WORD Attack Type] [DWORD Target Id] [BYTE Target Type] [WORD X] [WORD Y] 
6d   10   NPC Stop      6d [DWORD Unit Id] [WORD X] [WORD Y] [BYTE Unit Life] 
6e  1   <Unknown>         6e 
6f  1   <Unknown>         6f 
70  1   <Unknown>         70 
71  1   <Unknown>         71 
72  1   <Unknown>         72 
73  32   <Unknown>         ---------- 
74   10   Player Corpse Assign   74 [BYTE Assign 0x00 = False || 0x01 True] [DWORD Owner Id] [DWORD Corpse Id] 
75   13   Player Party Info   75 [DWORD Unit Id] [WORD Party Id] [WORD Char Level] [WORD Relationship] [WORD In Your Party? 0x00 = False || 0x01 = True] 
76   6   Player In Proximity   76 [BYTE Unit Type] [BYTE Unit Id] 
77   2   Button Actions      77 [BYTE Action] 
78   21   Trade Accepted      78 [NULLSTRING[16] Char Name] [DWORD Unit Id] 
79   6    Gold in Trade      79 [BYTE Gold Owner] [DWORD Amount] 
7a   13   Pet Action      7a [BYTE 0x00 = Unsummoned/Lost Sight || 0x01 = Summoned/Assign] [BYTE Skill] [WORD Pet Type] [DWORD Owner Id] [DWORD Pet Id] 
7b   8   Assign Skill Hotkey   7b [BYTE Slot] [BYTE Skill] [BYTE 0x00 = Right || 0x80 = Left] FF FF FF FF 
7c   6   Use Scroll      7c [BYTE Type] [DWORD Item Id] 
7d   18   Set Item State      --------- 
7e   5   <Unknown>                 --------- 
7f   10   Ally Party Info      7f  [BYTE Unit Type] [WORD Unit Life] [DWORD Unit Id] [DWORD Unit Area Id]    
80  -   <Unused>         ---------- 
81   20   Assign Merc      81 [BYTE Unknown] [WORD Merc Kind?] [DWORD Owner Id] [DWORD Merc Id] [DWORD Unknown] [DWORD Unknown] 
82   29   Portal Ownership   82 [DWORD Owner Id] [NULLSTRING[16] Owner Name] [DWORD Local Id] [DWORD Remote Id] 
83  -   <Unused>         ---------- 
84  -   <Unused>         ---------- 
85  -   <Unused>         ---------- 
86  -   <Unused>         ---------- 
87  -   <Unused>         ---------- 
88  -   <Unused>         ---------- 
89  2   Special Quest Event           89 [BYTE Event Id] 
8a   6   NPC Wants to Interact   8a [BYTE Unit Type] [DWORD Unit Id] 
8b   6   Player Relationship   8b [DWORD Unit Id] [BYTE 0x00 = No Party || 0x01 = In Party || 0x02 = Wants to Party] 
8c   11   Relationship Update   8c [DWORD Player 1 Id] [DWORD Player 2 Id] [WORD Relation State] 
8d   7   Assign Player To Party   8d [DWORD Player Id] [WORD Party Id] 
8e   10   Corpse Assign      8e [BYTE 0x00 = Unassign || 0x01 = Assign] [DWORD Owner Id] [DWORD Corpse Id] 
8f   33   Pong         8f [BYTES[32] 0x00] 
90   13   Party Automap Info   90 [DWORD Player Id] [DWORD Player X] [DWORD Player Y] 
91  26   <Unknown>         ---------- 
92  6   <Unknown>         ---------- 
93  8   <Unknown>         ---------- 
94   *   Base Skill Levels      94 [BYTE Amount of Skills] [DWORD Player Id] (for each skill->) [WORD Skill] [BYTE Level] 
95   13   Life and Mana Update   95 [WORD Unit Life] [WORD Unit Mana] [WORD Unit Stamina] [WORD X] [WORD Y] [WORD Unknown] 
96   9   Walk Verify      96 [WORD Stamina] [WORD X] [WORD Y] [WORD State] 
97   1   Weapon Switch      97 
98   7   <Unknown>         ---------- 
99   16   Skill Triggered      ---------- 
9a   17   <Unknown>         ---------- 
9b   7   (Merc Related?)         <Research Needed> 9b [WORD Unknown] [DWORD Unknown] 
9c   *   Item Action (World)   * 
9d   *   Item Action (Owned)   * 
9e   7   (BYTE)Merc Attribute   9e [BYTE Attribute] [DWORD Merc Id]  [BYTE Amount] 
9f   8   (WORD)Merc Attribute   9f [BYTE Attribute] [DWORD Merc Id] [WORD Amount] 
a0   10   (DWORD)Merc Attribute   a0 [BYTE Attribute] [DWORD Merc Id] [DWORD Amount] 
a1   7   (BYTE)Merc Add Exp.   ---------- 
a2   8  (WORD)Merc Add Exp.   ---------- 
a3   24   <Unknown>                   ---------- 
a4  3   <Unknown>         ---------- 
a5  8   <Unknown>         ---------- 
a6  *   <Unknown>         ---------- 
a7   7   Delayed State      a7 [BYTE Unit Type] [DWORD Unit Id] [BYTE State] 
a8   *   Set State      a8 [BYTE Unit Type] [DWORD Unit Id] [BYTE Packet Length] [BYTE State] [VOID State Effects] 
a9   7   End State      a9 [BYTE Unit Type] [DWORD Unit Id] [BYTE State] 
aa   *   Add Unit         aa [BYTE Unit Type] [DWORD Unit Id] [BYTE Packet Length] [VOID State Info] 
ab   7   NPC Heal      ab [BYTE Unit Type] [DWORD Unit Id] [BYTE Unit Life] 
ac   *   Assign NPC      ac [DWORD Unit Id] [WORD Unit Code] [WORD X] [WORD Y] [BYTE Unit Life] [BYTE Packet Length] [VOID State Info] 
ad  9   <Unknown>         ---------- 
ae   *   Warden Request      ae [WORD Packet Length Excluding Header] [VOID Data] 
af   2   Connection Info      af [BYTE ProtocolVer] 
b0   1   Game Connection Terminated   b0 
b1    53   <Unknown>                      --------- 
b2    *    <Unknown>                      --------- 
b3    5   IP Ban?                      b3 [DWORD Param?] 


*/

/*
C -> S
01   5   Walk            01 [WORD x] [WORD y] 
02   9   Walk to entity         02 [DWORD entity kind] [DWORD id] 
03   5   Run            03 [WORD x] [WORD y] 
04   9   Run to entity         04 [DWORD entity kind] [DWORD id] 
05   5   Shift Left Click Skill      05 [WORD x] [WORD y] 
06   9   Left Skill on unit      06 [DWORD entity kind] [DWORD id] 
07   9   Shift left skill on unit   07 [DWORD entity kind] [DWORD id] 
08   5   Shift Left skill (hold)      08 [WORD x] [WORD y] 
09   9   Left Skill on unit (hold)   09 [DWORD entity kind] [DWORD id] 
0a   9   Shift left skill unit (hold)   0a [DWORD entity kind] [DWORD id] 
0b   1   <Unknown>         0b 
0c   5   Right skill         0c [WORD x] [WORD y] 
0d   9   Right skill unit      0d [DWORD entity kind] [DWORD id] 
0e   9   Shift right skill unit      0e [DWORD entity kind] [DWORD id] 
0f   5   Right skill (hold)      0f [WORD x] [WORD y] 
10   9   Right skill unit (hold)      10 [DWORD entity kind] [DWORD id] 
11   9   Shift Right skill unit (hold)   11 [DWORD entity kind] [DWORD id] 
12   1   <Unknown>         12 
13   9   Interact (click) entity      13 [DWORD entity kind] [DWORD id] 
14   [Varies]Overhead Chat         14 00 00 [*char message] 00 00 00 
15   [Varies]Chat            15 01 00 [*char message] 00 00 00 
16   13   Pick item (ground)      16 04 00 00 00 [DWORD id] [DWORD inventory(0) or cursor (1)] 
17   5   Drop item (ground)      17 [DWORD id] 
18   17   Insert item in buffer      18 [DWORD id] [DWORD xpos] [DWORD ypos] [DWORD buffer] 
19   5   Remove item from buffer      19 [DWORD id] 
1a   9   Equip item         1a [DWORD id] [WORD position] 00 00 
1b   9   Swap 2 handed item      1b [DWORD id] [WORD position] 00 00 
1c   3   Remove body item      1c [WORD position] 
1d   9   Swap cursor item with body   1d [DWORD id] [WORD position] 00 00 
1e   9   Swap 2 1-handed items with a 2-handed item   1e [DWORD unknown] [DWORD unknown] 
1f   17   Swap cursor/buffer items   1f [DWORD cursor item id] [DWORD buffer item id] [DWORD xpos] [DWORD ypos] 
20   13   Activate buffer item      20 [DWORD id] [WORD x] 00 00 [WORD y] 00 00 
21   9   Stack items         21 [DWORD item to stack id] [DWORD item where it stacks id] 
22   5   Unstack items         22 [DWORD unknown] 
23   9   Item to belt         23 [DWORD id] [DWORD position] 
24   5   Item from belt         24 [DWORD id] 
25   9   Switch belt item      25 [DWORD cursor item][DWORD belt item] 
26   13   Use belt item         26 [DWORD id] [DWORD option] 00 00 00 00 
27   9   Identify item         27 [DWORD item id] [DWORD scroll id] 
28   9   Socket item         28 [DWORD item to socket id] [DWORD socketable item id] 
29   9   Scroll to book         29 [DWORD scroll id] [DWORD book id] 
2a   9   Item to cube (indirect)      2a [DWORD item id] [DWORD cube id] 
2b   --   Unused            ------------- 
2c   --   Unused (Logged as hack)      ------------- 
2d   --   Unused (Logged as hack)      ------------- 
2e   --   Unknown            ------------- 
2f   9   Initiate entity chat      2f [DWORD entity kind] [DWORD id] 
30   9   Terminate entity chat      30 [DWORD entity kind] [DWORD id] 
31   9   Quest message         31 [DWORD id] [DWORD message] 
32   17   Buy item from NPC buffer   32 [DWORD entity id] [DWORD item id] [DWORD tab] [DWORD cost] 
33   17   Sell item to NPC buffer      33 [DWORD entity id] [DWORD item id] [DWORD tab] [DWORD cost] 
34   5   Identify items with NPC      34 [DWORD entity id] 
35   17   Repair            35 [DWORD entity id] [DWORD item id] [DWORD tab] [DWORD cost?] 
36   9   Hire merc         36 [DWORD entity id] [DWORD merc id] 
37   5   Identify (from gamble)      37 [DWORD item id] 
38   13   Entity action         38 [DWORD action] [DWORD entity id] [DWORD complement] 
39   5   Purchase Life         39 [DWORD NPC id] 
3a   3   Add stat point         3a [WORD stat] 
3b   3   Add skill point         3b [WORD skill] 
3c   9   Select skill         3c [WORD skill] 00 [BYTE left (80) or right 00) skill] FF FF FF FF 
3d   5   Highlight a door      3d [DWORD object id]   (Logged as Mode (5) crash) 
3e   5   Activate Scroll of Inifuss   3e [DWORD scroll of infuss. id] 
3f   3   Play audio         3f [WORD sound message] 
40   1   Request Quest Data      40 
41   1   Resurrect         41 
42   --   Unknown/Unused         -------------- 
43   --   Unknown/Unused         -------------- 
44   17   Staff in orifice      44 [DWORD orifice entity kind] [DWORD orifice id] [DWORD staff id] [DWORD entity state] 
45   9   Change TP Location      45 [DWORD entity id] [WORD location] 00 00 (logged as hack) 
46   13   Have Merc Interact      46 [DWORD merc id] [DWORD entity id][DWORD entity type] 
47   13   Move Merc         47 [DWORD Merc ID] [WORD X] 00 00 [WORD Y] 00 00 
48   1   Turns off busy state      48 
49   9   Take WP/Close WP      49 [DWORD wp id] [BYTE destination] 00 00 00 
4a   --   Unused            -------------- 
4b   9   Request Entity Update      4b [DWORD entity type][DWORD entity id] 
4c   5   Transmorgify   4c [Object ID] 
4d   3   Play NPC Message      4d [WORD NPC Sound Message] 
4e   --   Unused            -------------- 
4f   7   Click Button         4f [DWORD button id] [WORD complement] 
50   9   Drop Gold         50 [DWORD player id] [DWORD gold pieces] 
51   9   Bind hotkey to skill      51 [BYTE skill]  [BYTE left (80) or right 00) skill] [WORD hotkey] FF FF FF FF 
52   5   <Unknown>         52 [DWORD unknown] 
53   1   Turn stamina on   (Not used)   53 
54   1   Turn stamina off (Not used)   54 
55   --   Unused            -------------- 
56   --   Unused            -------------- 
57   --   Unused            -------------- 
58   3   Quest Completed         58 [WORD Quest id] 
59   17   Make entity move      59 [DWORD entity kind] [DWORD entity id] [WORD x] 00 00 [WORD y] 00 00 
5a   --   Unused            -------------- 
5b   --   Unused            -------------- 
5c   --   Unused            -------------- 
5d   7   Squelch/Hostile         5d [BYTE button] [BYTE toggle on/off] [DWORD player id] 
5e   6   Invite Party         5e [BYTE button] [DWORD player id] 
5f   5   Update Player Pos      5f [WORD x] [WORD y] 
60   1   Swap weapons         60 
61   3   Drop/Pickup merc item      61 [WORD position (00 to drop)] 
62   5   Resurrect Merc         62 [DWORD npc id] 
63   5   Shift left-click item (to belt)   63 [DWORD item] 
64   9   <Hack Detection>         64 [DWORD unknown] [DWORD unknown] 
65   --   <Hack Detection>         65 
66   *   Warden Response         66 [BYTE Data Length] 00 [VARIABLE Data] 
67   --  --        -------------- 
68   37   Game Join Request         68 [DWORD Server Hash] [WORD Server Token] [BYTE Char Type] [DWORD VerByte (0x0b)] [DWORD Unknown] [DWORD Unknown] 00 [Char Name[15]] 00 
69   1   Leave Game            69 
6a   --   --         -------------- 
6b   1   Join Game            6b 
6c  --   --        -------------- 
6d  13  Ping           6d [DWORD Tickcount] [DWORD Delay] 00 00 00 00 
6e  --   Unknown/Unused            -------------- 
6f   --   Unknown/Unused            -------------- 


*/