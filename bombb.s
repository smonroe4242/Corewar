.name		"Test front bomb"
.comment	"spawn lfork wall forward"

		ld		%786432,r2
		ld		%0,r4
		ld		%-28,r5
live:	live	%-2
		sti		r2,%496,r4
		add		r5,r4,r4
		and		r6,r6,r6
		zjmp	%:live