//
// Created by dar on 4/29/16.
//

#ifndef C003_LEVELDATA_H
#define C003_LEVELDATA_H

#include <string>
#include <vector>


class LevelData {

public:
    using type = std::vector<std::string>;

    void addLevel(const std::string &name);
    type getLevels() const;

private:
    type levels;
};

#endif //C003_LEVELDATA_H
