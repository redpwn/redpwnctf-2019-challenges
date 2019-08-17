gone = ['open','file','execfile','compile','reload','__import__','eval','input']
for func in gone:
    del __builtins__.__dict__[func]
print 'wow! again, there\'s a file called flag.txt! insane!'
while True:
    try:
      x = raw_input()      
      if " " in x:
       print "no spaces!"
       exit()    
      print "now it's ", x, "!"
      exec 'x=' + x
    except Exception, e:
      print 'Exception: ', e
