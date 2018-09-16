.name		"Loud Mouth"
.comment	"Aff shit talker"

	sti		r1,%:go,%1
	ld		%129412,r2
	ld		%32,r3
	ld		%1,r4
go:	live	%-1
	aff		r2
	aff		r3
#	add		r2,r4,r2
	and		r9,r9,r9
	zjmp	%:go