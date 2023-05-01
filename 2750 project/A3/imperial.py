
class Length:
    def __init__( self, feet=0, inches=0, txt="" ):
        self.feet = feet;
        self.inches = inches;
        self.normalize();

    def normalize( self ):
        total_inches = self.feet*12 + self.inches;
        self.feet = total_inches // 12;
        self.inches = total_inches % 12;

    def __str__( self ):
        return '''%d'%d"''' % (self.feet, self.inches,);

    def __add__( self, other ):
        l = Length( feet=self.feet+other.feet,inches=self.inches+other.inches );
        l.normalize();
        return l;

if __name__=="__main__":
    l1 = Length( feet=5, inches=3 );
    l2 = Length( feet=2, inches=10 );
    l3 = Length( feet=2.5 );

    print( l1, l2, l3 );
    print( l1 + l2 );
    print( l2 + l3 );
