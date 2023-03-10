/**
 * @file test.cpp
 * @author Narissa Tsuboi
 */

/*
 * Test detector skips comments.
 */

/** Skip me! **/
/* Skip me! */
// Skip me!
// Skip me! //////////////////////////////////////////////////////////////////
// int function();
// int function() {

/*
 * Test detector skips blank lines.
 */











/*
 * Test main detects functions.
 */





/*
 * Test main detects functions but not instantiations.
 */
// detect
Cat::Cat()
Cat()

// skip
Cat myCat = new Cat();




