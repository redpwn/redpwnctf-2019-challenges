from os import system
inp = input("What you thought you sed\n")
rep = '/' + input("What you aren't sure you sed\n") +  '/' 
new = input("What you actually sed\n")
cmd = 's' + rep + new + "/g"
if "'" not in new:
	cmd += "'"
print("You actually said")

system("echo '" + inp + "' | sed '" +  cmd)

