enum Terrain{
	PLAIN = 0,
	HILL = 1, //defensive bonus, ranged bonus
	TREES = 2, //defensive bonus, no ranged attacks
	DITCH = 3, //defensive malus, especially ranged
	BOULDER = 4, //impassible
	WATER = 5, //speed, offensive malus, no ranged attacks. defensive malus to ranged
};