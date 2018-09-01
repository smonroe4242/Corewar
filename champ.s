.name           "Steven"
.comment        "Just a basic Winner Program"

		ld		%4,r3
		sti		r1,%:live,%1
		ld		%786432,r15
		sti		r15,%100,%100
live:	live	%1
		ld		%655340,r1
#		fork	%:live
		add		r2,r3,r2
		sti		r1,%10,r2
		sub		r1,r3,r1
		zjmp	%:live
