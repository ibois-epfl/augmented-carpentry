class DuoBeam(Beam):
    def __init__(self):
        super().__init__()
        self.nbr_pieces = 2

my_duo = DuoBeam()
my_duo.calculate_volume()


class Beam:
    def __init__(self, length=2, width=0.2, height=0.5):
        self.length = length
        self.width = width
        self.height = height

    def calculate_volume(self):
        return self.length * self.width * self.height



class GlulamBeam(Beam):
    def __init__(self, layers):
        super().__init__()
        self.layers = layers

my_glulam = GlulamBeam(5)
print(my_glulam.calculate_volume())



class SolidBeam(Beam):
    def __init__(self, width, species):
        super().__init__(width)
        self.species = species

my_solid = SolidBeam(0.4, "oak")
print(my_solid.calculate_volume())



class LogBeam(Beam):
    def __init__(self, radius):
        super().__init__(width)
        self.radius = radius

    def calculate_volume(self):  # overriding the method
        return 3.14 * (self.width / 2) ** 2 * self.length

my_log = LogBeam(0.2)
print(my_log.calculate_volume())


class Stud:
    def __init__(self, position, is_vertical=True, width=0.2, height=0.5):
        self.position = position
        self.is_vertical = is_vertical
        self.width = width
        self.height = height

class Frame:
    def __init__(self, length=2, studs=None):
        self.length = length
        self.studs = studs or []

    def add_stud(self, stud):
        self.studs.append(stud)

# create the studs
stud_A = Stud((0, 0, 0))
stud_B = Stud((0.5, 0, 0))
stud_C = Stud((1, 0, 0))
stud_D = Stud((0, 0, 0), is_vertical=False)
stud_E = Stud((0, 2, 0), is_vertical=False)

# create the frame
frame = Frame()

# add the studs to the frame
frame.add_stud(stud_A)
frame.add_stud(stud_B)
frame.add_stud(stud_C)
frame.add_stud(stud_D)
frame.add_stud(stud_E)
