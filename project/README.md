# Korgkant - A SWEDISH DISC GOLF GAME
#### <https://www.youtube.com/watch?v=0Ud8UbEs-1Q&ab_channel=AnnaLindroos>
#### I have made a website for Swedish disc golfers. The idea is to be able to go disc golfing with an easy-access fun twist. There is a card game called "RIPT Revenge" made by Innova Disc Golf on which I have based my website, although I have translated the content to Swedish to be able to reach the entire disc golf community in my home town. I also wanted the disc golfers to be able to access this game via their phones - instead of having to bring a card game into the disc golf course. My website renders two cards that will show up on the screen, and the cards contain text with different challenges. The user can click one of the cards to make the other card invisible, and the user can also choose to press a "Next" button at the top of the page in order to render two new cards to choose from. I have chosen a color palette which is a mix of three different colors based on the colors used by ***JomezPro***, which is a popular disc golf media company that covers tournaments as well as disc golf news, and therefore a lot of disc golfers are familiar with that company and those colors.

#### The files in my project are the following:
1. **flask_session**
2. **script.js**
3. **styles.css**
4. **index.html**
5. **layout.html**
6. **app.py**
7. **discgolf.db**

## 1
#### The **flask_session** file is auto-generated by the microframework Flask when building the website.

## 2
#### The **script.js** file contains Javascript to make the website more dynamic and interactive. It contains a function, "run" that will run when the DOM has been fully loaded and parsed. "run" uses the "getElementById" function to get two elements \(in the form of cards\) from the document. It then adds eventListeners to the two cards, and when either of those cards are clicked, the non-clicked card is hidden and the clicked card moves to the center of the page. To accomplish this, it changes the following CSS properties of the cards:
- position
- top
- left
- transform
- display
## 3
#### The **styles.css** file contains some CSS to alter the aesthetics of my webpage. One of the CSS selectors is the "card-body", in which I've styled the cards to be a pastel pink color with black text using the "background-color" and "color" properties. I've also selected both cards by id "#firstCard" and "#secondCard" and used the "font-family" property to give them the *Helvetica* font. The color of my webpage is a linear gradient mix of blue and green. The selector is called ".gradient" and I used the height, witdh and background-image properties in order to achieve these colors. The "body" selector contains CSS for the color behind the linear gradient colors, which is a green color set with the "background-color" property. The small text at the bottom of my page has an id of "#footer" which I've designed to be centered using the following properties:
- position
- left
- bottom
- transform
- margin
## 4
#### The **index.html** file is an extension of the file **layout.html** using Jinja syntax, in order to make the file a bit more concise. The HTML in the index file contains a button for rendering two new cards, and then two cards with HTML from Bootstrap. The two cards have different id's \(#firstCard and #secondCard\) to interact with them individually in Javascript. I've used Jinja Syntax in order to display the two random cards that my SQL-database is giving the file.

## 5
#### The **layout.html** file contains standard HTML like "!DOCTYPE html" and similar necessities. It also contains the bootstrap links needed to use HTML, CSS and JS from Bootstrap, as well as links to my **styles.css** file and my **script.js** file. Then the file includes the body of my webpage, whose class I've set to be "gradient" which I've styled in my css stylesheet. I've then set the main class to contain the index.html file with Jinja Syntax. After that there's a div that contains text with information about which game my website is based on.

## 6
#### The **app.py** file contains some libraries and functions from: *os*, *cs50*, *flask* and *flask_session*. The file then configures the application using Flask, and ensure templates are auto-reloaded. It then configures the session to use filesystem. To use my SQLite database the file then configures the CS50 library. Then a single route is added, "/" \(to the index.html file\) using GET only. The index function is then declared: it contains one variable for the first card on the webpage, and uses db.execute to select random data \(in the form of one sentence\) from my Sqlite database. I also declare a variable called "double", which extracts the id from the SQL sentence that the function returns. The other variable - for the second card on the webpage - does the same as the first variable, except that it passes in the "double" variable in order to avoid getting the same data on the two cards. The function then renders the template \(index.html\), passing in the two variables for the cards.

## 7
#### The **discgolf.db** file contains the link to my SQLite database which contains a single table "Discgolf". This table has two fields: firstly "id" of type integer, which is the primary key for the table and also has an autoincrement for each insertion of data into the table. The second field is called "challenge" and contains text which is displayed on the cards.

