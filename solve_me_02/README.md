###PUZZLE

Background:	The	term	"search"	is	pretty general.	So	far,	we	have	only	dealt	with	searching	for	elements	

in	an	array.	This behavior	is	very	much	like	search	and	update in	a	database	of	information,	and	we	will	

likely spend	more	time	improving	this	search	later	in the	course.	But	this	is	not	the	only	type	of search.	

The	general	approach	can	be	extended to:	solving	numerical	systems,	planning,	AI strategy,	and	path	

finding,	to	name	just	a	few.

The	input	will	be	a	2-dimensional	array	A[n][n] of	numbers,	representing	the	topographic	map	of	a	

geographic	surface	— each	of	the	entries	representing	the	elevation	[above	sea	level].	Also	among	the	

input	will	be	a	starting	location	(r,c),	referring	to	entry	A[r][c].

If	you	were	planning	hiking	trails,	you	would be	bound	by	the	differences	in	elevation	between	

neighboring	entries.	For	the	purposes	of	this	question,	a person	could	traverse	between	two	adjacent	

locations,	if	their	elevations	differ by	no	more	than	2.	Adjacency	follows	just	the	4	standard	compass	

directions, i.e.,	no	diagonals.	Thus,	a	point	on	the	map	is	considered	reachable	if	it	is traversable	from	

A[r][c] through	any	sequence	of	adjacent	entries.

Your	task	is	to	write	an	algorithm	that	computes	all	of	the	reachable	locations in	the	grid.	The	output	will	

be	another	2-D	array	R[n][n]	with	true/false values	— true	means	reachable,	false	means	unreachable.

Sample

Suppose	A[10][10] looks	like	this,	for	starting	location	A[0][0]:

```
50 51 54 58 60 60 60 63 68 71

48 52 51 59 60 60 63 63 69 70

44 48 52 55 58 61 64 64 66 69

44 46 53 52 57 60 60 61 65 68

42 45 50 54 59 61 63 63 66 70

38 42 46 56 56 63 64 61 64 62

36 40 44 50 58 60 66 65 62 61

36 39 42 49 56 62 67 66 65 60

30 36 40 47 50 64 64 63 62 60

50 50 50 50 50 50 50 50 50 50
```

Both	south	and	east	are	traversable	from	the	start.	However,	going	south leads	to	a	dead	end	because	

44	and	52	are	too	far	away.	Here's	the	map again,	but	with	reachable	entries	highlighted:
```

50 51 54 58 60 60 60 63 68 71

48 52 51 59 60 60 63 63 69 70

44 48 52 55 58 61 64 64 66 69

44 46 53 52 57 60 60 61 65 68

42 45 50 54 59 61 63 63 66 70

38 42 46 56 56 63 64 61 64 62

36 40 44 50 58 60 66 65 62 61

36 39 42 49 56 62 67 66 65 60

30 36 40 47 50 64 64 63 62 60

32 34 38 45 51 53 58 58 57 57
```

Thus,	the	resulting	array	should	be:
```

1 1 0 0 0 0 0 1 0 0

1 1 1 0 0 0 1 1 0 0

0 0 1 0 0 0 1 1 1 0

0 0 1 1 0 0 0 0 1 0

0 0 0 1 0 0 0 0 1 0

0 0 0 1 1 0 0 0 1 1

0 0 0 0 1 1 0 0 1 1

0 0 0 0 1 1 0 0 0 1

0 0 0 0 0 1 1 1 1 1

0 0 0 0 0 0 0 0 0 0
```
