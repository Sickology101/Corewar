.name: "Honky Joe"
.comment: "Wanted dead or olive"

dead:	sti r1, %:live, %1
		and r1, %0, r1
		ld %70, r3
		zjmp %:dead
		ld %15, r3
		ld	10, r4
		sub r3, r4, r3
		st r3, -162
		st r3, -173
		st r3, -184
		st r3, -195
		st r3, -206

live:	live %1
		zjmp %:live
