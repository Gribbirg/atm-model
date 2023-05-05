#include "System.h"

int main() {
    System applicationClass(nullptr);
    applicationClass.build_tree_objects();
    return applicationClass.exec_app();
}
