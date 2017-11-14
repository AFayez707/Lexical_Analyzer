//
// Created by abdelrahman on 14/11/17.
//

#ifndef LEXICAL_ANALYZER_IDGENERATOR_H
#define LEXICAL_ANALYZER_IDGENERATOR_H

class IDGenerator {

private:
    IDGenerator();
    static int count;

public:
    static int getNextID();
};

#endif //LEXICAL_ANALYZER_IDGENERATOR_H
