import random

# Define a list of anime-related questions
questions = [
    ["What is the name of the main character in Naruto?", "Sasuke", "Naruto", "Kakashi", "Sakura", 2],
    ["Which anime features a character named Edward Elric?", "One Piece", "Fullmetal Alchemist", "Attack on Titan", "Naruto", 2],
    ["In which anime do characters collect Dragon Balls?", "Dragon Ball Z", "Naruto", "Bleach", "One Punch Man", 1],
    ["What is the name of the organization that opposes the main character in Death Note?", "The FBI", "The Task Force", "Kira", "The Shinigami", 2],
    ["Which anime features a school for heroes?", "My Hero Academia", "Fairy Tail", "Bleach", "One Piece", 1],
    ["What is the primary weapon used by Shinigami in Bleach?", "Guns", "Swords", "Ninja Tools", "Magic", 2],
    ["What is the title of the anime about a group of pirates searching for the One Piece?", "One Piece", "Hunter x Hunter", "Naruto", "Sword Art Online", 1],
    ["In which anime does a character named Light Yagami appear?", "Death Note", "Code Geass", "Bleach", "Fairy Tail", 1],
    ["What is the name of the main female character in Attack on Titan?", "Mikasa", "Sasha", "Armin", "Annie", 1],
    ["Which anime features a character who can manipulate time with a watch?", "Steins;Gate", "Your Name", "Re:Zero", "Dragon Ball", 1],
    ["What is the name of the cat in Sailor Moon?", "Luna", "Artemis", "Nyan", "Chibi", 1],
    ["Which anime features a character named Guts?", "Berserk", "Attack on Titan", "Naruto", "Bleach", 1],
    ["What is the primary goal of the characters in Hunter x Hunter?", "To become a Hunter", "To find a treasure", "To defeat villains", "To save the world", 1],
    ["In what anime does the character Inuyasha appear?", "Inuyasha", "Naruto", "One Piece", "Sword Art Online", 1],
    ["What is the main theme of the anime Attack on Titan?", "Pirates", "Demons", "Zombies", "Titans", 4],
    ["Which anime involves a death game with a deadly twist?", "Sword Art Online", "Naruto", "One Piece", "Fairy Tail", 1],
]

# Shuffle questions to randomize order
random.shuffle(questions)

c = "y"
levels = [1000, 2000, 3000, 5000, 10000, 20000, 40000, 80000, 160000, 320000, 640000, 1250000, 2500000, 5000000, 10000000, 70000000]
money = 0

while c.lower() == 'y':
    for i in range(len(questions)):
        question = questions[i]
        print(f"\nQuestion for Rs.{levels[i]} is on your screen:")
        print(f"{question[0]}")
        print(f"1. {question[1]}     2. {question[2]}")
        print(f"3. {question[3]}     4. {question[4]}")

        try:
            reply = int(input("Please enter the correct answer (1 to 4) or 0 to quit: "))
        except ValueError:
            print("Invalid input! Please enter a number between 1 and 4, or 0 to quit.")
            continue

        # Handle quitting scenarios
        if reply == 0:
            if i <= 4:
                print(f"You chose to quit. You get Rs.{levels[max(i-1, 0)]}.")
            elif i <= 9:
                print(f"You chose to quit. You get Rs.10,000.")
            elif i <= 16:
                print(f"You chose to quit. You get Rs.{levels[max(i-1, 0)]}.")
            break

        if reply == question[5]:
            print(f"Correct answer! You won Rs.{levels[i]}")
        else:
            print("Sorry, wrong answer!")
            if i < 5:
                print(f"Your take-home money is Rs.{levels[max(i-1, 0)]}")
            elif i < 10:
                print("Your take-home money is Rs.10,000")
            elif i < 16:
                print("Your take-home money is Rs.320,000")
            break
    else:
        print("Congratulations on answering all the questions! You've won Rs.7 Crores!")

    c = input("Do you want to play again? (y/n): ")

print("Game END\nThank You For playing")
