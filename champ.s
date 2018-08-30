.name           "Steven"
.comment        "Just a basic Winner Program"

	sti		r1,%15,%1
	and		r1,%0,r1
	live	%1
	zjmp	%-5
