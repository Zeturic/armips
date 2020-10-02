.psx
.create "output.bin", 0

.strictarea 20h
	.word 1,2,3,4
.endarea

.area 20h
	.strictarea 20h
		.word 1,2,3,4
	.endarea
.endarea

.strictarea 20h
	.strictarea 20h
		.word 1,2,3,4
	.endarea
.endarea

.close
