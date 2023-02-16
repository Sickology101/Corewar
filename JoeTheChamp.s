.name "Honky Joe"
.comment "Wanted dead or olive"

dead:	ld %7, r3
		zjmp %:live
		ld %15, r3
		ld	10, r4
		sub r3, r4, r3
		st r3, -162

live:	live %1
		zjmp %:dead
