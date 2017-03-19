#define _NOTSHOW_ -2
#define _USERDEF_ -1

BYTE anMonsterColours[1000] = {
    _USERDEF_, //0 Skeleton
    _USERDEF_, //1 Returned
    _USERDEF_, //2 BoneWarrior
    _USERDEF_, //3 BurningDead
    _USERDEF_, //4 Horror
    _USERDEF_, //5 Zombie
    _USERDEF_, //6 HungryDead
    _USERDEF_, //7 Ghoul
    _USERDEF_, //8 DrownedCarcass
    _USERDEF_, //9 PlagueBearer
    _USERDEF_, //10 Afflicted
    _USERDEF_, //11 Tainted
    _USERDEF_, //12 Misshapen
    _USERDEF_, //13 Disfigured
    _USERDEF_, //14 Damned
    _USERDEF_, //15 FoulCrow
    _USERDEF_, //16 BloodHawk
    _USERDEF_, //17 BlackRaptor
    _USERDEF_, //18 CloudStalker
    _USERDEF_, //19 Fallen
    _USERDEF_, //20 Carver
    _USERDEF_, //21 Devilkin
    _USERDEF_, //22 DarkOne
    _USERDEF_, //23 WarpedFallen
    _USERDEF_, //24 Brute
    _USERDEF_, //25 Yeti
    _USERDEF_, //26 Crusher
    _USERDEF_, //27 WailingBeast
    _USERDEF_, //28 GargantuanBeast
    _USERDEF_, //29 SandRaider
    _USERDEF_, //30 Marauder
    _USERDEF_, //31 Invader
    _USERDEF_, //32 Infidel
    _USERDEF_, //33 Assailant
    _USERDEF_, //34 unused, Gorgon
    _USERDEF_, //35 unused, StoneStalker
    _USERDEF_, //36 unused, SerpentQueen
    _USERDEF_, //37 unused, StygianWatcher
    _USERDEF_, //38 Ghost
    _USERDEF_, //39 Wraith
    _USERDEF_, //40 Specter
    _USERDEF_, //41 Apparition
    _USERDEF_, //42 DarkShape
    _USERDEF_, //43 DarkHunter
    _USERDEF_, //44 VileHunter
    _USERDEF_, //45 DarkStalker
    _USERDEF_, //46 BlackRogue
    _USERDEF_, //47 FleshHunter
    _USERDEF_, //48 DuneBeast
    _USERDEF_, //49 RockDweller
    _USERDEF_, //50 JungleHunter
    _USERDEF_, //51 DoomApe
    _USERDEF_, //52 TempleGuard
    _USERDEF_, //53 MoonClan
    _USERDEF_, //54 NightClan
    _USERDEF_, //55 BloodClan
    _USERDEF_, //56 HellClan
    _USERDEF_, //57 DeathClan
    _USERDEF_, //58 FallenShaman
    _USERDEF_, //59 CarverShaman
    _USERDEF_, //60 DevilkinShaman
    _USERDEF_, //61 DarkShaman
    _USERDEF_, //62 WarpedShaman
    _USERDEF_, //63 QuillRat
    _USERDEF_, //64 SpikeFiend
    _USERDEF_, //65 ThornBeast
    _USERDEF_, //66 RazorSpine
    _USERDEF_, //67 JungleUrchin
    _USERDEF_, //68 SandMaggot
    _USERDEF_, //69 RockWorm
    _USERDEF_, //70 Devourer
    _USERDEF_, //71 GiantLamprey
    _USERDEF_, //72 WorldKiller
    _USERDEF_, //73 TombViper
    _USERDEF_, //74 ClawViper
    _USERDEF_, //75 Salamander
    _USERDEF_, //76 PitViper
    _USERDEF_, //77 SerpentMagus
    _USERDEF_, //78 SandLeaper
    _USERDEF_, //79 CaveLeaper
    _USERDEF_, //80 TombCreeper
    _USERDEF_, //81 TreeLurker
    _USERDEF_, //82 RazorPitDemon
    _USERDEF_, //83 Huntress
    _USERDEF_, //84 SaberCat
    _USERDEF_, //85 NightTiger
    _USERDEF_, //86 HellCat
    _USERDEF_, //87 Itchies
    _USERDEF_, //88 BlackLocusts
    _USERDEF_, //89 PlagueBugs
    _USERDEF_, //90 HellSwarm
    _USERDEF_, //91 DungSoldier
    _USERDEF_, //92 SandWarrior
    _USERDEF_, //93 Scarab
    _USERDEF_, //94 SteelWeevil
    _USERDEF_, //95 AlbinoRoach
    _USERDEF_, //96 DriedCorpse
    _USERDEF_, //97 Decayed
    _USERDEF_, //98 Embalmed
    _USERDEF_, //99 PreservedDead
    _USERDEF_, //100 Cadaver
    _USERDEF_, //101 HollowOne
    _USERDEF_, //102 Guardian
    _USERDEF_, //103 Unraveler
    _USERDEF_, //104 Horadrim Ancient
    _USERDEF_, //105 Baal Subject Mummy
    _USERDEF_, //106 unused, DamnedHorde
    _USERDEF_, //107 unused, TwistedHorde
    _USERDEF_, //108 unused, WickedHorde
    _USERDEF_, //109 unused, UnholyHorde
    _USERDEF_, //110 CarrionBird
    _USERDEF_, //111 UndeadScavenger
    _USERDEF_, //112 HellBuzzard
    _USERDEF_, //113 WingedNightmare
    _USERDEF_, //114 Sucker
    _USERDEF_, //115 Feeder
    _USERDEF_, //116 BloodHook
    _USERDEF_, //117 BloodWing
    _USERDEF_, //118 Gloam
    _USERDEF_, //119 SwampGhost
    _USERDEF_, //120 BurningSoul
    _USERDEF_, //121 BlackSoul
    _USERDEF_, //122 Arach
    _USERDEF_, //123 SandFisher
    _USERDEF_, //124 PoisonSpinner
    _USERDEF_, //125 FlameSpider
    _USERDEF_, //126 SpiderMagus
    _USERDEF_, //127 ThornedHulk
    _USERDEF_, //128 BrambleHulk
    _USERDEF_, //129 Thrasher
    _USERDEF_, //130 Spikefist
    _USERDEF_, //131 GhoulLord
    _USERDEF_, //132 NightLord
    _USERDEF_, //133 DarkLord
    _USERDEF_, //134 BloodLord
    _USERDEF_, //135 Banished
    _USERDEF_, //136 DesertWing
    _USERDEF_, //137 Fiend
    _USERDEF_, //138 Gloombat
    _USERDEF_, //139 BloodDiver
    _USERDEF_, //140 DarkFamiliar
    _USERDEF_, //141 RatMan
    _USERDEF_, //142 Fetish
    _USERDEF_, //143 Flayer
    _USERDEF_, //144 SoulKiller
    _USERDEF_, //145 StygianDoll
    _NOTSHOW_, //146 DeckardCain
    _NOTSHOW_, //147 Gheed
    _NOTSHOW_, //148 Akara
    _NOTSHOW_, //149 dummy, chicken
    _NOTSHOW_, //150 Kashya
    _NOTSHOW_, //151 dummy, rat
    _NOTSHOW_, //152 Dummy, RogueTown
    _NOTSHOW_, //153 Dummy, HellMeteor
    _NOTSHOW_, //154 Charsi
    _NOTSHOW_, //155 Warriv
    _USERDEF_, //156 Andariel
    _NOTSHOW_, //157 dummy, Smallbird
    _NOTSHOW_, //158 dummy, Largebird
    _NOTSHOW_, //159 dummy, Bat
    _USERDEF_, //160 DarkRanger
    _USERDEF_, //161 VileArcher
    _USERDEF_, //162 DarkArcher
    _USERDEF_, //163 BlackArcher
    _USERDEF_, //164 FleshArcher
    _USERDEF_, //165 DarkSpearwoman
    _USERDEF_, //166 VileLancer
    _USERDEF_, //167 DarkLancer
    _USERDEF_, //168 BlackLancer
    _USERDEF_, //169 FleshLancer
    _USERDEF_, //170 SkeletonArcher
    _USERDEF_, //171 ReturnedArcher
    _USERDEF_, //172 BoneArcher
    _USERDEF_, //173 BurningDeadArcher
    _USERDEF_, //174 HorrorArcher
    _NOTSHOW_, //175 Warriv
    _NOTSHOW_, //176 Atma
    _NOTSHOW_, //177 Drognan
    _NOTSHOW_, //178 Fara
    _NOTSHOW_, //179 dummy, Cow
    _USERDEF_, //180 SandMaggotYoung
    _USERDEF_, //181 RockWormYoung
    _USERDEF_, //182 DevourerYoung
    _USERDEF_, //183 GiantLampreyYoung
    _USERDEF_, //184 WorldKillerYoung
    _NOTSHOW_, //185 dummy, Camel
    _USERDEF_, //186 Blunderbore
    _USERDEF_, //187 Gorbelly
    _USERDEF_, //188 Mauler
    _USERDEF_, //189 Urdar
    _USERDEF_, //190 SandMaggotEgg
    _USERDEF_, //191 RockWormEgg
    _USERDEF_, //192 DevourerEgg
    _USERDEF_, //193 GiantLampreyEgg
    _USERDEF_, //194 WorldKillerEgg
    _NOTSHOW_, //195 dummy, Act2Male
    _NOTSHOW_, //196 Dummy, Act2Female
    _NOTSHOW_, //197 dummy, Act2Child
    _NOTSHOW_, //198 Greiz
    _NOTSHOW_, //199 Elzix
    _NOTSHOW_, //200 Geglash
    _NOTSHOW_, //201 Jerhyn
    _NOTSHOW_, //202 Lysander
    _NOTSHOW_, //203 Dummy, Act2Guard
    _NOTSHOW_, //204 dummy, Act2Vendor1
    _NOTSHOW_, //205 dummy, Act2Vendor2
    _USERDEF_, //206 FoulCrowNest
    _USERDEF_, //207 BloodHawkNest
    _USERDEF_, //208 BlackVultureNest
    _USERDEF_, //209 CloudStalkerNest
    _NOTSHOW_, //210 Meshif
    _USERDEF_, //211 Duriel
    _USERDEF_, //212 Undead RatMan
    _USERDEF_, //213 Undead Fetish
    _USERDEF_, //214 Undead Flayer
    _USERDEF_, //215 Undead SoulKiller
    _USERDEF_, //216 Undead StygianDoll
    _USERDEF_, //217 unused, DarkGuard
    _USERDEF_, //218 unused, DarkKnight
    _USERDEF_, //219 unused, BloodGuard
    _USERDEF_, //220 unused, BloodKnight
    _USERDEF_, //221 unused, DarkPaladin
    _USERDEF_, //222 unused, BloodMage
    _USERDEF_, //223 unused, Demonist
    _USERDEF_, //224 unused, BlackMagus
    _USERDEF_, //225 unused, Diabolist
    _USERDEF_, //226 unused, DeathMage
    _NOTSHOW_, //227 Maggot
    _USERDEF_, //228 MummyGenerator
    _USERDEF_, //229 Radament
    _USERDEF_, //230 unused, FireBeast
    _USERDEF_, //231 unused, IceGlobe
    _USERDEF_, //232 unused, LightningBeast
    _USERDEF_, //233 unused, PoisonOrb
    _USERDEF_, //234 FlyingScimitar
    _USERDEF_, //235 Zakarumite
    _USERDEF_, //236 Faithful
    _USERDEF_, //237 Zealot
    _USERDEF_, //238 Sexton
    _USERDEF_, //239 Cantor
    _USERDEF_, //240 Heirophant
    _USERDEF_, //241 Heirophant
    _USERDEF_, //242 Mephisto
    _USERDEF_, //243 Diablo
    _NOTSHOW_, //244 DeckardCain
    _NOTSHOW_, //245 DeckardCain
    _NOTSHOW_, //246 DeckardCain
    _USERDEF_, //247 Swamp Dweller
    _USERDEF_, //248 Bog Creature
    _USERDEF_, //249 Slime Prince
    _USERDEF_, //250 Summoner
    _NOTSHOW_, //251 tyrael
    _NOTSHOW_, //252 asheara
    _NOTSHOW_, //253 hratli
    _NOTSHOW_, //254 alkor
    _NOTSHOW_, //255 ormus
    _USERDEF_, //256 izual
    _NOTSHOW_, //257 halbu
    _USERDEF_, //258 WaterWatcherLimb
    _USERDEF_, //259 RiverStalkerLimb
    _USERDEF_, //260 StygianWatcherLimb
    _USERDEF_, //261 WaterWatcherHead
    _USERDEF_, //262 RiverStalkerHead
    _USERDEF_, //263 StygianWatcherHead
    _NOTSHOW_, //264 meshif
    _NOTSHOW_, //265 DeckardCain
    _NOTSHOW_, //266 navi (flavie)
    _USERDEF_, //267 Bloodraven
    _NOTSHOW_, //268 Dummy, bug
    _NOTSHOW_, //269 Dummy, scorpion
    _USERDEF_, //270 RogueScout
    _USERDEF_, //271 Dummy, RogueHireling (act1 hireling)
    _NOTSHOW_, //272 Dummy, RogueTownShoot
    _USERDEF_, //273 GargoyleTrap
    _USERDEF_, //274 ReturnedMage
    _USERDEF_, //275 BoneMage
    _USERDEF_, //276 BurningDeadMage
    _USERDEF_, //277 HorrorMage
    _USERDEF_, //278 RatManShaman
    _USERDEF_, //279 FetishShaman
    _USERDEF_, //280 FlayerShaman
    _USERDEF_, //281 SoulKillerShaman
    _USERDEF_, //282 StygianDollShaman
    _NOTSHOW_, //283 larva
    _USERDEF_, //284 SandMaggotQueen
    _USERDEF_, //285 RockWormQueen
    _USERDEF_, //286 DevourerQueen
    _USERDEF_, //287 GiantLampreyQueen
    _USERDEF_, //288 WorldKillerQueen
    _USERDEF_, //289 ClayGolem
    _USERDEF_, //290 BloodGolem
    _USERDEF_, //291 IronGolem
    _USERDEF_, //292 FireGolem
    _NOTSHOW_, //293 Dummy, Familiar
    _NOTSHOW_, //294 Dummy, Act3Male
    _USERDEF_, //295 NightMarauder
    _NOTSHOW_, //296 Dummy, Act3Female
    _NOTSHOW_, //297 Natalya
    _USERDEF_, //298 FleshSpawner
    _USERDEF_, //299 StygianHag
    _USERDEF_, //300 Grotesque
    _USERDEF_, //301 FleshBeast
    _USERDEF_, //302 StygianDog
    _USERDEF_, //303 GrotesqueWyrm
    _USERDEF_, //304 Groper
    _USERDEF_, //305 Strangler
    _USERDEF_, //306 StormCaster
    _USERDEF_, //307 Corpulent
    _USERDEF_, //308 CorpseSpitter
    _USERDEF_, //309 MawFiend
    _USERDEF_, //310 DoomKnight
    _USERDEF_, //311 AbyssKnight
    _USERDEF_, //312 OblivionKnight
    _USERDEF_, //313 QuillBear
    _USERDEF_, //314 SpikeGiant
    _USERDEF_, //315 ThornBrute
    _USERDEF_, //316 RazorBeast
    _USERDEF_, //317 GiantUrchin
    _NOTSHOW_, //318 Dummy, Snake
    _NOTSHOW_, //319 Dummy, Parrot
    _NOTSHOW_, //320 Dummy, Fish
    _NOTSHOW_, //321 Dummy, Evil Hole
    _NOTSHOW_, //322 Dummy, Evil Hole
    _NOTSHOW_, //323 Dummy, Evil Hole
    _NOTSHOW_, //324 Dummy, Evil Hole
    _NOTSHOW_, //325 Dummy, Evil Hole
    _NOTSHOW_, //326 a trap, trapfirebolt
    _NOTSHOW_, //327 a trap
    _NOTSHOW_, //328 a trap (act2 wall, act3 totem)
    _NOTSHOW_, //329 a trap, trappoison
    _NOTSHOW_, //330 a trap, trapchainlightning
    _NOTSHOW_, //331 Kaelan
    _NOTSHOW_, //332 Dummy, InvisoSpawner
    _USERDEF_, //333 unused, DiabloClone
    _USERDEF_, //334 SuckerNest
    _USERDEF_, //335 FeederNest
    _USERDEF_, //336 BloodHookNest
    _USERDEF_, //337 BloodWingNest
    _USERDEF_, //338 Guard (act2 hireling)
    _NOTSHOW_, //339 Dummy, MiniSpider
    _USERDEF_, //340 x, PrisonFL
    _USERDEF_, //341 x, PrisonFR
    _USERDEF_, //342 x, PrisonBL
    _USERDEF_, //343 x, PrisonBR
    _NOTSHOW_, //344 Dummy, Bonewall*
    _USERDEF_, //345 Council Member
    _USERDEF_, //346 Council Member
    _USERDEF_, //347 Council Member
    _USERDEF_, //348 Turret1
    _USERDEF_, //349 Turret2
    _USERDEF_, //350 Turret3
    _NOTSHOW_, //351 Hydra1
    _NOTSHOW_, //352 Hydra2
    _NOTSHOW_, //353 Hydra3
    _USERDEF_, //354 a trap, pillar
    _NOTSHOW_, //355 Dummy, seven tombs
    _USERDEF_, //356 Dopplezon
    _USERDEF_, //357 Valkyrie
    _NOTSHOW_, //358 Dummy, Act2Hireling
    _NOTSHOW_, //359 Iron Wolf (act3 town+hireling)*
    _USERDEF_, //360 Balrog
    _USERDEF_, //361 PitLord
    _USERDEF_, //362 VenomLord
    _USERDEF_, //363 NecroSkeleton (necro skel)
    _USERDEF_, //364 NecroMage (necro mage)
    _USERDEF_, //365 Griswold
    _NOTSHOW_, //366 compellingorb
    _NOTSHOW_, //367 tyrael
    _NOTSHOW_, //368 youngdiablo
    _NOTSHOW_, //369 a trap, nova
    _USERDEF_, //370 Dummy, SpiritMummy
    _USERDEF_, //371 LightningSpire
    _USERDEF_, //372 FireTower
    _USERDEF_, //373 Slinger
    _USERDEF_, //374 SpearCat
    _USERDEF_, //375 NightSlinger
    _USERDEF_, //376 HellSlinger
    _NOTSHOW_, //377 Dummy, Boba Fett
    _NOTSHOW_, //378 Dummy, Darth Maul
    _USERDEF_, //379 ReturnedMage
    _USERDEF_, //380 BoneMage
    _USERDEF_, //381 BaalColdMage
    _USERDEF_, //382 HorrorMage
    _USERDEF_, //383 ReturnedMage
    _USERDEF_, //384 BoneMage
    _USERDEF_, //385 BurningDeadMage
    _USERDEF_, //386 HorrorMage
    _USERDEF_, //387 ReturnedMage
    _USERDEF_, //388 BoneMage
    _USERDEF_, //389 BurningDeadMage
    _USERDEF_, //390 HorrorMage
    _USERDEF_, //391 Hell Bovine
    _NOTSHOW_, //392 x, window right (act4 window)*
    _NOTSHOW_, //393 x, window left (act4 window)*
    _USERDEF_, //394 SpearCat
    _USERDEF_, //395 NightSlinger
    _USERDEF_, //396 RatMan
    _USERDEF_, //397 Fetish
    _USERDEF_, //398 Flayer
    _USERDEF_, //399 SoulKiller
    _USERDEF_, //400 StygianDoll
    _NOTSHOW_, //401 Dummy, Mephisto Spirit
    _USERDEF_, //402 The Smith
    _NOTSHOW_, //403 TrappedSoul*
    _NOTSHOW_, //404 TrappedSoul*
    _NOTSHOW_, //405 Jamella
    _NOTSHOW_, //406 Izual's Ghost
    _USERDEF_, //407 RatMan
    _NOTSHOW_, //408 Malachai?
    _USERDEF_, //409 The Feature Creep
    _NOTSHOW_, //410 Wake of Destruction
    _NOTSHOW_, //411 Charged Bolt Sentry
    _NOTSHOW_, //412 Lightning Sentry
    _NOTSHOW_, //413 Blade Creeper (blade sentinel)
    _NOTSHOW_, //414 Invis Pet*
    _NOTSHOW_, //415 Inferno Sentry
    _NOTSHOW_, //416 Death Sentry
    _USERDEF_, //417 Shadow Warrior
    _USERDEF_, //418 Shadow Master
    _USERDEF_, //419 Druid Hawk*
    _USERDEF_, //420 Druid Spirit Wolf
    _USERDEF_, //421 Druid Fenris (dire wolf)
    _USERDEF_, //422 Spirit of Barbs
    _USERDEF_, //423 Heart of Wolverine
    _USERDEF_, //424 Oak Sage
    _USERDEF_, //425 Druid Plague Poppy (poison creeper)*
    _USERDEF_, //426 Druid Cycle of Life (carrion vine)*
    _USERDEF_, //427 Vine Creature (solar creeper)*
    _USERDEF_, //428 Druid Bear
    _USERDEF_, //429 Eagle
    _USERDEF_, //430 Wolf
    _USERDEF_, //431 Bear
    _NOTSHOW_, //432 Barricade Door*
    _NOTSHOW_, //433 Barricade Door*
    _NOTSHOW_, //434 Prison Door*
    _NOTSHOW_, //435 Barricade Tower*
    _USERDEF_, //436 RotWalker
    _USERDEF_, //437 ReanimatedHorde
    _USERDEF_, //438 ProwlingDead
    _USERDEF_, //439 UnholyCorpse
    _USERDEF_, //440 DefiledWarrior
    _USERDEF_, //441 Siege Beast
    _USERDEF_, //442 CrushBiest
    _USERDEF_, //443 BloodBringer
    _USERDEF_, //444 GoreBearer
    _USERDEF_, //445 DeamonSteed
    _USERDEF_, //446 SnowYeti1
    _USERDEF_, //447 SnowYeti2
    _USERDEF_, //448 SnowYeti3
    _USERDEF_, //449 SnowYeti4
    _USERDEF_, //450 WolfRider1
    _USERDEF_, //451 WolfRider2
    _USERDEF_, //452 WolfRider3
    _USERDEF_, //453 Minionexp
    _USERDEF_, //454 Slayerexp
    _USERDEF_, //455 IceBoar
    _USERDEF_, //456 FireBoar
    _USERDEF_, //457 HellSpawn
    _USERDEF_, //458 IceSpawn
    _USERDEF_, //459 GreaterHellSpawn
    _USERDEF_, //460 GreaterIceSpawn
    _USERDEF_, //461 FanaticMinion
    _USERDEF_, //462 BerserkSlayer
    _USERDEF_, //463 ConsumedFireBoar
    _USERDEF_, //464 ConsumedIceBoar
    _USERDEF_, //465 FrenziedHellSpawn
    _USERDEF_, //466 FrenziedIceSpawn
    _USERDEF_, //467 InsaneHellSpawn
    _USERDEF_, //468 InsaneIceSpawn
    _USERDEF_, //469 Succubusexp
    _USERDEF_, //470 VileTemptress
    _USERDEF_, //471 StygianHarlot
    _USERDEF_, //472 Hell Temptress
    _USERDEF_, //473 Blood Temptress
    _USERDEF_, //474 Dominus
    _USERDEF_, //475 VileWitch
    _USERDEF_, //476 StygianFury
    _USERDEF_, //477 Blood Witch
    _USERDEF_, //478 Hell Witch
    _USERDEF_, //479 OverSeer
    _USERDEF_, //480 Lasher
    _USERDEF_, //481 OverLord
    _USERDEF_, //482 BloodBoss
    _USERDEF_, //483 HellWhip
    _USERDEF_, //484 MinionSpawner
    _USERDEF_, //485 MinionSlayerSpawner
    _USERDEF_, //486 MinionIce/fireBoarSpawner
    _USERDEF_, //487 MinionIce/fireBoarSpawner
    _USERDEF_, //488 Minionice/hellSpawnSpawner
    _USERDEF_, //489 MinionIce/fireBoarSpawner
    _USERDEF_, //490 MinionIce/fireBoarSpawner
    _USERDEF_, //491 Minionice/hellSpawnSpawner
    _USERDEF_, //492 Imp1
    _USERDEF_, //493 Imp2
    _USERDEF_, //494 Imp3
    _USERDEF_, //495 Imp4
    _USERDEF_, //496 Imp5
    _USERDEF_, //497 CatapultS
    _USERDEF_, //498 CatapultE
    _USERDEF_, //499 CatapultSiege
    _USERDEF_, //500 CatapultW
    _USERDEF_, //501 Frozen Horror1
    _USERDEF_, //502 Frozen Horror2
    _USERDEF_, //503 Frozen Horror3
    _USERDEF_, //504 Frozen Horror4
    _USERDEF_, //505 Frozen Horror5
    _USERDEF_, //506 Blood Lord1
    _USERDEF_, //507 Blood Lord2
    _USERDEF_, //508 Blood Lord3
    _USERDEF_, //509 Blood Lord4
    _USERDEF_, //510 Blood Lord5
    _NOTSHOW_, //511 Larzuk
    _NOTSHOW_, //512 Drehya
    _NOTSHOW_, //513 Malah
    _NOTSHOW_, //514 Nihlathak Town
    _NOTSHOW_, //515 Qual-Kehk
    _NOTSHOW_, //516 Catapult Spotter S (target?)
    _NOTSHOW_, //517 Catapult Spotter E (target?)
    _NOTSHOW_, //518 Catapult Spotter Siege (target?)
    _NOTSHOW_, //519 Catapult Spotter W
    _NOTSHOW_, //520 DeckardCain
    _NOTSHOW_, //521 tyrael
    0xcb, //522 Act 5 Combatant (barb fighter)*
    _NOTSHOW_, //523 Act 5 Combatant*
    _NOTSHOW_, //524 Barricade Wall Right*
    _NOTSHOW_, //525 Barricade Wall Left*
    _USERDEF_, //526 Nihlathak outside town
    _NOTSHOW_, //527 Drehya outside town
    _USERDEF_, //528 Evil hut
    _USERDEF_, //529 Death Mauler1
    _USERDEF_, //530 Death Mauler2
    _USERDEF_, //531 Death Mauler3
    _USERDEF_, //532 Death Mauler4
    _USERDEF_, //533 Death Mauler5
    _NOTSHOW_, //534 POW (captured barb)*
    _NOTSHOW_, //535 Act 5 Townguard
    _NOTSHOW_, //536 Act 5 Townguard
    _NOTSHOW_, //537 Ancient Statue 1
    _NOTSHOW_, //538 Ancient Statue 2
    _NOTSHOW_, //539 Ancient Statue 3
    _USERDEF_, //540 Ancient Barbarian 1
    _USERDEF_, //541 Ancient Barbarian 2
    _USERDEF_, //542 Ancient Barbarian 3
    _NOTSHOW_, //543 Baal Throne
    _USERDEF_, //544 Baal Crab
    _NOTSHOW_, //545 Baal Taunt (invis follower)
    _USERDEF_, //546 Putrid Defiler1
    _USERDEF_, //547 Putrid Defiler2
    _USERDEF_, //548 Putrid Defiler3
    _USERDEF_, //549 Putrid Defiler4
    _USERDEF_, //550 Putrid Defiler5
    _USERDEF_, //551 Pain Worm1
    _USERDEF_, //552 Pain Worm2
    _USERDEF_, //553 Pain Worm3
    _USERDEF_, //554 Pain Worm4
    _USERDEF_, //555 Pain Worm5
    _NOTSHOW_, //556 Bunny
    _USERDEF_, //557 Council Member
    _USERDEF_, //558 VenomLord
    _NOTSHOW_, //559 Baal Crab to Stairs
    _USERDEF_, //560 Act 5 Hireling 1hs
    _USERDEF_, //561 Act 5 Hireling 2hs (act5 hireling)
    _USERDEF_, //562 Baal Tentacle
    _USERDEF_, //563 Baal Tentacle
    _USERDEF_, //564 Baal Tentacle
    _USERDEF_, //565 Baal Tentacle
    _USERDEF_, //566 Baal Tentacle
    _NOTSHOW_, //567 Injured Barbarian 1 (town barb)
    _NOTSHOW_, //568 Injured Barbarian 2 (town barb)
    _NOTSHOW_, //569 Injured Barbarian 3 (town barb)
    _USERDEF_, //570 Baal Crab Clone
    _USERDEF_, //571 Baals Minion
    _USERDEF_, //572 Baals Minion
    _USERDEF_, //573 Baals Minion
    _NOTSHOW_, //574 Worldstone Effect
    _USERDEF_, //575
    _USERDEF_, //576
    _USERDEF_, //577
    _USERDEF_, //578
    _USERDEF_, //579
    _USERDEF_, //580
    _USERDEF_, //581
    _USERDEF_, //582
    _USERDEF_, //583
    _USERDEF_, //584
    _USERDEF_, //585
    _USERDEF_, //586
    _USERDEF_, //587
    _USERDEF_, //588
    _USERDEF_, //589
    _USERDEF_, //590
    _USERDEF_, //591
    _USERDEF_, //592
    _USERDEF_, //593
    _USERDEF_, //594
    _USERDEF_, //595
    _USERDEF_, //596
    _USERDEF_, //597
    _USERDEF_, //598
    _USERDEF_, //599
    _USERDEF_, //600
    _USERDEF_, //601
    _USERDEF_, //602
    _USERDEF_, //603
    _USERDEF_, //604
    _USERDEF_, //605
    _USERDEF_, //606
    _USERDEF_, //607
    _USERDEF_, //608
    _USERDEF_, //609
    _USERDEF_, //610
    _USERDEF_, //611
    _USERDEF_, //612
    _USERDEF_, //613
    _USERDEF_, //614
    _USERDEF_, //615
    _USERDEF_, //616
    _USERDEF_, //617
    _USERDEF_, //618
    _USERDEF_, //619
    _USERDEF_, //620
    _USERDEF_, //621
    _USERDEF_, //622
    _USERDEF_, //623
    _USERDEF_, //624
    _USERDEF_, //625
    _USERDEF_, //626
    _USERDEF_, //627
    _USERDEF_, //628
    _USERDEF_, //629
    _USERDEF_, //630
    _USERDEF_, //631
    _USERDEF_, //632
    _USERDEF_, //633
    _USERDEF_, //634
    _USERDEF_, //635
    _USERDEF_, //636
    _USERDEF_, //637
    _USERDEF_, //638
    _USERDEF_, //639
    _USERDEF_, //640
    _USERDEF_, //641
    _USERDEF_, //642
    _USERDEF_, //643
    _USERDEF_, //644
    _USERDEF_, //645
    _USERDEF_, //646
    _USERDEF_, //647
    _USERDEF_, //648
    _USERDEF_, //649
    _USERDEF_, //650
    _USERDEF_, //651
    _USERDEF_, //652
    _USERDEF_, //653
    _USERDEF_, //654
    _USERDEF_, //655
    _USERDEF_, //656
    _USERDEF_, //657
    _USERDEF_, //658
    _USERDEF_, //659
    _USERDEF_, //660
    _USERDEF_, //661
    _USERDEF_, //662
    _USERDEF_, //663
    _USERDEF_, //664
    _USERDEF_, //665
    _USERDEF_, //666
    _USERDEF_, //667
    _USERDEF_, //668
    _USERDEF_, //669
    _USERDEF_, //670
    _USERDEF_, //671
    _USERDEF_, //672
    _USERDEF_, //673
    _USERDEF_, //674
    _USERDEF_, //675
    _USERDEF_, //676
    _USERDEF_, //677
    _USERDEF_, //678
    _USERDEF_, //679
    _USERDEF_, //680
    _USERDEF_, //681
    _USERDEF_, //682
    _USERDEF_, //683
    _USERDEF_, //684
    _USERDEF_, //685
    _USERDEF_, //686
    _USERDEF_, //687
    _USERDEF_, //688
    _USERDEF_, //689
    _USERDEF_, //690
    _USERDEF_, //691
    _USERDEF_, //692
    _USERDEF_, //693
    _USERDEF_, //694
    _USERDEF_, //695
    _USERDEF_, //696
    _USERDEF_, //697
    _USERDEF_, //698
    _USERDEF_, //699
    _USERDEF_, //700
    _USERDEF_, //701
    _USERDEF_, //702
    _USERDEF_, //703
    _USERDEF_, //704
    _USERDEF_, //705
    _USERDEF_, //706
    _USERDEF_, //707
    _USERDEF_, //708
    _USERDEF_, //709
    _USERDEF_, //710
    _USERDEF_, //711
    _USERDEF_, //712
    _USERDEF_, //713
    _USERDEF_, //714
    _USERDEF_, //715
    _USERDEF_, //716
    _USERDEF_, //717
    _USERDEF_, //718
    _USERDEF_, //719
    _USERDEF_, //720
    _USERDEF_, //721
    _USERDEF_, //722
    _USERDEF_, //723
    _USERDEF_, //724
    _USERDEF_, //725
    _USERDEF_, //726
    _USERDEF_, //727
    _USERDEF_, //728
    _USERDEF_, //729
    _USERDEF_, //730
    _USERDEF_, //731
    _USERDEF_, //732
    _USERDEF_, //733
};
