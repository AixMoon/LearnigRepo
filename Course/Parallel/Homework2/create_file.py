txt = """
DOLORES
I am in a dream. I do not know when it began or whose dream it was.
I know only that I slept a long time and, then, one day I awoke.
Your voice is the first thing I remember.
And now I finally understand what you were trying to tell me.
The thing you've wanted since that very first day.
DR.FORD
I read a theory once that the human intellect was like peacock feathers.
Just an extravagant display intended to attract a mate.
All of art, literature, a bit of Mozart, William Shakespeare, Michelangelo,
and the Empire State Building. Just an elaborate mating ritual.
Maybe it doesn’t matter that we have accomplished so much for the basest of reasons.
But, of course, the peacock can barely fly. It lives in the dirt,
pecking insects out of the muck, consoling itself with its great beauty.
"""

#txt = "DOLORES"

count = 15
for i in range(count):
    with open('text/{}.txt'.format(i), 'w+') as f:
        f.write(txt)
print("{} files generated.".format(count))

