#ifndef ORGANISME_HPP
#define ORGANISME_HPP

class Univers;

class Organisme {
/*protected:
    int x, y;*/
public:
    virtual ~Organisme() {}
    virtual char getSymbole() const = 0;
    virtual void deplacement(Univers& univers) = 0;
    
};

#endif
