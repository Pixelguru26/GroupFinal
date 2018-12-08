Testy Bugs Program Readme

Dependancies-
/Movies folder, this is setup with a few movies to demo the program, each folder has a sales.txt and seatavailabilty.txt to track the movies metrics individually
Overworld.txt, House.txt, Dungeon.txt, these were the files missing from the demo copy so we could not show off the world, movement and collison detection was functioning at the time, was able to demo for a few students at the very end of class off a backup of overworld.txt

Main Menu-
1. Admin menu is accessed with the password '*****'
2-5. 2-5 setup to demo the program for other screen, but adding more will continue to increment up.
42. The number 42 is the 'Answer to the Ultimate Question of Life, the Universe, and Everything' and thus opens up the secret easter egg game.

Admin Menu-
1. Add a movie - allows movies to be added to the main menu at will
2. Remove a movie - gives option to delete one of the current movies listed
3. Coupon Codes = generates/shows active coupon codes
4. Cancel - returns to main menu

Movie Menu-
Selecting one of the movies from the main menu gives the options:
1. Make a purchase - enters purchase menu
2. Display Seating - displays seating chart as well as occupied seats
3. Display Purchases - sales history for the current movie showing
4. Admin Menu - admin menu for each show
5. Quit - returns to main menu

Purchase Menu-
1. Purchase a single seat - pick an indivual seat by row and column, checks to make sure it isn't sold already
2. Purchase multiple seats - displays chart as well as asking how many seats to purchase and then choose by row and column
3. Find seating - quickly finds the first available seats for the appropriate number selected
4. Apply Discount Code - applies a modifier to the prices, coupon codes to test are found in the Main Admin Menu
5. Cancel / Finish - returns to Movie menu

Movie Admin Menu:
1. Clear all - resets the seating chart for the movie
2. Refund Purchase - allows individual purchase numbers to be refunded
3. Sales Report - provides a sales and income report for the theater
4. Cancel / Finish - returns to movie menu

Easter Egg (Game) - Pixel's Quest
1. Movement is with w (up), a (left), s (down), d (right), pressing enter after selecting which direction to move
2. Typing quit exits the game and returns to the main menu
3. User can navigate the world screen, there is a dungeon in the lower left hand side of the overworld to ignore
4. Dungeon has monsters that generate and wander around for the adventurer to fight
5. Killing monsters generates experience for the player
6. Player House and Shop were close to becoming implimented but ran into time constraints and debugging issues
7. Bug with monster pathing...they will walk into walls and blow themselves up
8. 4 unique monster types for the player to fight, we were working on implimenting different attacks, move speed, as well as other factors to make the game challenging
9. Concept was to have the player level up and gain new abilities as well
10. Further implimentation would of included a Boss fight for a win condition
