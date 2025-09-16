# coding refresher practice

def word_count(text):
    counts = {}

    for word in text.split():
        # find the count of each word in a text string
        counts[word] = counts.get(word, 0) + 1
    return counts
print(word_count("the cat and the hat"))


# OOP practice 
import math

#object class
class Projectile:

    # constructor
    def __init__(self, vel, angDeg):
        self.vel = vel
        self.angDeg = math.radians(angDeg) # convert angle to radians

    # method to calculate position
    def position(self, t):
        g = 9.81
        #kinematic equations
        x = self.vel * math.cos(self.angDeg) * t
        y = self.vel * math.sin(self.angDeg) * t - 0.5 * g * t**2
        return (x, y)
    
# create an instance of the class
p = Projectile(50, 45)
print(p.position(2))  # get position at t=2 seconds

# Unit testing practice
def test_Projectile():
    p = Projectile(10, 90)
    x, y = p.position(1)
    assert round(x, 2) == 0.0
    assert y > 0.0
test_Projectile()
print("All tests passed.")


