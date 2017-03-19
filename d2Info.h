/*
3. 暗金物品中具有Chance to cast Skill Level可变属性其等级的确定

暗黑2毁灭之王中的 UNIQUE Items，有的会带有xx% Chance to cast Level ?? Skill on attack/on striking/when struck技能。存在以下两种情况。一种是其中的Skill Level是唯一确定了的，例如雷神之力 - 巨战腰带 [Thundergod's Vigor - War Belt] 包含的属性5% Chance to cast Level 7 Fist of the Heavens when struck。还有一种是不确定的，这个不确定的Skill Level在一个范围内可变。例如光之军刀 - 幻化之刃 [Lightsabre - Phase Blade]包含的属性5% Chance to cast Level 14-20 Chain Lightning on attack(可变)。这个可变属性是完全随机靠所谓的RP来决定的吗？NO！其实并非如此

该可变属性由物品等级ilvl与相对应人物使用该Skill的最小等级Skill REQ（以上面提到的光之军刀为例，其中的Chain Lightning是SOR角色技能，SOR学习这个技能的最低人物等级要求为LV18。那么Skill REQ=18）。Skill Level不确定的时候，是先将Skill Level设为0，再利用物品等级ilvl和Skill REQ计算，针对D2X 1。10的计算公式如下：

Skill Level = (ilvl - Skill REQ)/4 + 1 （小数忽略不计，计算结果向下取整）

众所周知，ilvl在1-99间变化，但UNIQUE Items有专有的Qlvl，即需要一定的ilvl才能出现（详细可参考http://www.diabloii.net相关内容），所以Skill Level的变化范围并不是很极端

仍然以光之军刀为例来说明

通过资料得知，光之军刀在D2X 1.10里可能出现的最低物品等级为ilvl=73，至于最高的物品等级毫无疑问就是K BALL所得到的ilvl=99了，即ilvl = 73 ~ 99。而Skill REQ=18，带入公式：

Skill Level = (73-18)/4 + 1 ~ (99-18)/4 +1 = 14 -> 20

以下给出在D2X 1.10中属性带有可变Chance to cast Skill Level的物品列表（如有遗漏，敬请指出）

碎骨者之忍 - 哥德之斧 [Boneslayer Blade - Gothic Axe]
50% chance to cast level 12-20 holy bolt when struck

地狱毁灭者 - 斩首斧 [Hellslayer - Decapitator]
10% chance to cast level 16-20 fire ball on attack

光之军刀 - 幻化之刃 [Lightsabre - Phase Blade]
5% chance to cast level 14-20 chain lightning on attack

雪之冲突 - 战场腰带 [Snowclash - Battle Belt]
5% chance to cast level 7-19 blizzard when struck

暴风骑士 - 战斗斧 [Stormrider - Tabar]
10% chance to cast level 13-20 charged bolt on striking

旭日东升 - 项链 [The Rising Sun - Amulets]
2% chance to cast level 13-19 meteor when struck

通过公式计算我们可以了解到，如果你打算拥有完全JP的旭日东升 - 项链 和 雪之冲突 - 战场腰带，依靠MF则只有K BAAL老大（Diablo CLONE因其只能DROP USC暂且忽略）才有机会获得（哦？除了MF还有那些途径？呵呵，其它方法自然是有的，例如你自认RP一向8错，可以用LV95以上的人物去赌博嘛……$@)*%#$%#^#&，嘻嘻。另语云：“ROB才是王道”，这个，我就不多说了……），其它Monsters，包括mlvl级别仅次于巴尔的Nihlathak也没有这等好货色，更不消说Mephisto、Pindleskin之流……

附：针对D2X 1.09的公式为Skill Level = ilvl/3 - Skill REQ + 1。有余力的朋友请自己验证吧







*/