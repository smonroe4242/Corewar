.name		"Hopper"
.comment	"Happiness is an lfork away"

		ld		%786432,r2		#00 0c 00 00
		ld		%1,r4
		ld		%2,r5
		ld		%16777216,r10	#01 00 00 00
		ld		%746498,r11		#00 0b 64 02
		ld		%-32766972,r12	#fe 0c 04 04
		ld		%1409614852,r13	#54 05 04 04
		ld		%106169862,r14	#06 54 06 06
		ld		%101318635,r15	#06 09 ff eb

live:	live	%42				#5
		st		r10,-501		#5
		st		r11,-502		#5
		st		r1,-510
		st		r12,-508			#5
		st		r13,-509		#5
		st		r14,-510		#5
		st		r15,-511		#5
		lfork	%-541			#3
		and		r8,r8,r8
		zjmp	%:live			#3
