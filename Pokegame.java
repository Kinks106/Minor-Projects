import java.util.Scanner;
import java.util.Stack;
import java.util.Random;

class Pokemon {
    private String name;
    private int hp;
    private int maxHp;  // Save the original HP
    private int atk;
    private int def;
    private int spd;
    private String type;
    private String[] moves;

    public Pokemon(String name, int hp, int atk, int def, int spd, String type, String[] moves) {
        this.name = name;
        this.hp = hp;
        this.maxHp = hp;  // Store the original HP
        this.atk = atk;
        this.def = def;
        this.spd = spd;
        this.type = type;
        this.moves = moves;
    }

    public String getName() {
        return name;
    }

    public int getHp() {
        return hp;
    }

    public void setHp(int hp) {
        this.hp = Math.max(0, hp); // Ensure HP doesn't go below 0
    }

    public int getAtk() {
        return atk;
    }

    public int getDef() {
        return def;
    }

    public int getSpd() {
        return spd; // Add getSpd method
    }

    public String getType() {
        return type;
    }

    public String[] getMoves() {
        return moves;
    }

    public void takeDamage(int damage) {
        this.hp -= damage;
        if (this.hp < 0) {
            this.hp = 0;
        }
    }

    // Reset HP to full (max HP)
    public void resetHP() {
        this.hp = maxHp;
    }

    public void displayStats() {
        System.out.println(name + " [Type: " + type + "] HP: " + hp + " ATK: " + atk + " DEF: " + def + " SPD: " + spd);
    }
}

class Node {
    Pokemon data;
    Node next;

    public Node(Pokemon data) {
        this.data = data;
        this.next = null;
    }
}

class List {
    private Node head;

    public void addPokemon(Pokemon p) {
        Node newNode = new Node(p);
        if (head == null) {
            head = newNode;
        } else {
            Node current = head;
            while (current.next != null) {
                current = current.next;
            }
            current.next = newNode;
        }
    }

    public void displayPokemons() {
        Node current = head;
        while (current != null) {
            current.data.displayStats();
            current = current.next;
        }
    }

    public Pokemon getFirst() {
        return head != null ? head.data : null;
    }

    public void removeFaintedPokemon() {
        if (head != null && head.data.getHp() <= 0) {
            head = head.next;  // Remove the fainted Pokemon from the list
        }
    }

    public boolean hasRemainingPokemon() {
        return head != null;
    }

    public Node getHeadNode() {
        return head;
    }
}

class Movestack {
    private Stack<String> moves = new Stack<>();

    public void pushMove(String move) {
        moves.push(move);
    }

    public String popMove() {
        return moves.isEmpty() ? null : moves.pop();
    }

    public void displayMoveHistory() {
        System.out.println("Move History: " + moves);
    }
}

public class Pokegame {
    public static void main(String[] args) {
        // Pokémon Creation with unique moves
        Pokemon charmanderTemplate = new Pokemon("Charmander", 100, 60, 50, 65, "fire", new String[]{"Ember", "Flamethrower", "Scratch", "Growl"});
        Pokemon bulbasaurTemplate = new Pokemon("Bulbasaur", 110, 55, 55, 45, "grass", new String[]{"Vine Whip", "Razor Leaf", "Tackle", "Growl"});
        Pokemon squirtleTemplate = new Pokemon("Squirtle", 120, 50, 60, 43, "water", new String[]{"Water Gun", "Bubble", "Tackle", "Tail Whip"});

        List player1list = new List();
        List player2list = new List();

        // Player selection
        System.out.println("Welcome trainers to the Battle Dome. Let’s see who will reign supreme in this epic clash of Pokémon!");
        System.out.println("1. Charmander, the fiery lizard.");
        System.out.println("2. Squirtle, the water turtle.");
        System.out.println("3. Bulbasaur, the grass-type warrior.");

        System.out.println("\nPlayer 1, select 2 Pokémon to lead you to victory:");
        selectPokemon(player1list, charmanderTemplate, bulbasaurTemplate, squirtleTemplate);
        System.out.println("\nPlayer 2, select 2 Pokémon to claim your triumph:");
        selectPokemon(player2list, charmanderTemplate, bulbasaurTemplate, squirtleTemplate);

        // Display selected Pokémon
        System.out.println("\nPlayer 1’s battle squad is ready for action:");
        player1list.displayPokemons();
        System.out.println("\nPlayer 2’s Pokémon are gearing up for an all-out battle:");
        player2list.displayPokemons();

        // Initialize move stacks
        Movestack player1MoveStack = new Movestack();
        Movestack player2MoveStack = new Movestack();

        // Battle start
        System.out.println("\n--- Battle Start! ---");
        System.out.println("The battlefield crackles with anticipation...");

        Random rand = new Random();
        int rand_int = rand.nextInt(2) + 1;
        if (rand_int == 1) {
            System.out.println("It’s heads! Player 1 strikes first!");
        } else {
            System.out.println("It’s tails! Player 2 takes the lead!");
        }

        while (player1list.hasRemainingPokemon() && player2list.hasRemainingPokemon()) {
            Node player1CurrentPokemon = player1list.getHeadNode();
            Node player2CurrentPokemon = player2list.getHeadNode();

            System.out.println("\n🔴 **Current Battle: " + player1CurrentPokemon.data.getName() + " (Player 1) VS. " + player2CurrentPokemon.data.getName() + " (Player 2)!** 🔴");

            // Player 1's turn
            battleTurn(player1CurrentPokemon, player2CurrentPokemon, new Scanner(System.in), player1MoveStack);
            if (player2CurrentPokemon.data.getHp() <= 0) {
                System.out.println("\n💀 **" + player2CurrentPokemon.data.getName() + " has fainted!** 💀");
                player2list.removeFaintedPokemon();
                if (!player2list.hasRemainingPokemon()) {
                    System.out.println("🏆 Player 1 wins! 🏆 All of Player 2’s Pokémon have fainted!");
                    break;
                }
            }

            if (player2list.hasRemainingPokemon()) {
                battleTurn(player2CurrentPokemon, player1CurrentPokemon, new Scanner(System.in), player2MoveStack);
                if (player1CurrentPokemon.data.getHp() <= 0) {
                    System.out.println("\n💀 **" + player1CurrentPokemon.data.getName() + " has fainted!** 💀");
                    player1list.removeFaintedPokemon();
                    if (!player1list.hasRemainingPokemon()) {
                        System.out.println("🏆 Player 2 wins! 🏆 All of Player 1’s Pokémon have fainted!");
                        break;
                    }
                }
            }

            if (player1list.hasRemainingPokemon() && player2list.hasRemainingPokemon()) {
                System.out.println("\n🌟 **Round Summary:** 🌟");
                System.out.println(player1CurrentPokemon.data.getName() + " (Player 1) has " + player1CurrentPokemon.data.getHp() + " HP remaining!");
                System.out.println(player2CurrentPokemon.data.getName() + " (Player 2) has " + player2CurrentPokemon.data.getHp() + " HP remaining!");
            }
        }

        // Display move history
        System.out.println("\n📜 **Player 1's Move History** 📜");
        player1MoveStack.displayMoveHistory();
        System.out.println("\n📜 **Player 2's Move History** 📜");
        player2MoveStack.displayMoveHistory();
    }

    // Method to handle Pokémon selection
    public static void selectPokemon(List playerList, Pokemon charmander, Pokemon bulbasaur, Pokemon squirtle) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Select your Pokémon (Choose 1 and then 2):");
        System.out.println("1. Charmander");
        System.out.println("2. Bulbasaur");
        System.out.println("3. Squirtle");

        int firstChoice = sc.nextInt();
        int secondChoice = sc.nextInt();

        if (firstChoice == 1) {
            playerList.addPokemon(new Pokemon("Charmander", charmander.getHp(), charmander.getAtk(), charmander.getDef(), charmander.getSpd(), charmander.getType(), charmander.getMoves()));
        } else if (firstChoice == 2) {
            playerList.addPokemon(new Pokemon("Bulbasaur", bulbasaur.getHp(), bulbasaur.getAtk(), bulbasaur.getDef(), bulbasaur.getSpd(), bulbasaur.getType(), bulbasaur.getMoves()));
        } else if (firstChoice == 3) {
            playerList.addPokemon(new Pokemon("Squirtle", squirtle.getHp(), squirtle.getAtk(), squirtle.getDef(), squirtle.getSpd(), squirtle.getType(), squirtle.getMoves()));
        }

        if (secondChoice == 1) {
            playerList.addPokemon(new Pokemon("Charmander", charmander.getHp(), charmander.getAtk(), charmander.getDef(), charmander.getSpd(), charmander.getType(), charmander.getMoves()));
        } else if (secondChoice == 2) {
            playerList.addPokemon(new Pokemon("Bulbasaur", bulbasaur.getHp(), bulbasaur.getAtk(), bulbasaur.getDef(), bulbasaur.getSpd(), bulbasaur.getType(), bulbasaur.getMoves()));
        } else if (secondChoice == 3) {
            playerList.addPokemon(new Pokemon("Squirtle", squirtle.getHp(), squirtle.getAtk(), squirtle.getDef(), squirtle.getSpd(), squirtle.getType(), squirtle.getMoves()));
        }
    }

    // Handle turn-based battle logic
    public static void battleTurn(Node attacker, Node defender, Scanner sc, Movestack moveStack) {
        System.out.println(attacker.data.getName() + " attacks! Choose a move:");
        String[] moves = attacker.data.getMoves();
        for (int i = 0; i < moves.length; i++) {
            System.out.println((i + 1) + ". " + moves[i]);
        }
        int moveChoice = sc.nextInt();

        String chosenMove = moves[moveChoice - 1];
        moveStack.pushMove(chosenMove);
        System.out.println(attacker.data.getName() + " used " + chosenMove + "!");

        int damage = calculateDamage(attacker.data, defender.data);
        defender.data.takeDamage(damage);
        System.out.println(defender.data.getName() + " took " + damage + " damage!");
    }

    // More balanced damage calculation
    public static int calculateDamage(Pokemon attacker, Pokemon defender) {
        Random rand = new Random();
        double effectiveness = 1.0;

        // Type advantages (simplified)
        if (attacker.getType().equals("fire") && defender.getType().equals("grass")) {
            effectiveness = 2.0;
        } else if (attacker.getType().equals("water") && defender.getType().equals("fire")) {
            effectiveness = 2.0;
        } else if (attacker.getType().equals("grass") && defender.getType().equals("water")) {
            effectiveness = 2.0;
        } else if (attacker.getType().equals(defender.getType())) {
            effectiveness = 0.5;  // Same-type is less effective
        }

        // Base damage calculation considering attacker's attack and defender's defense
        int baseDamage = Math.max(10, attacker.getAtk() - defender.getDef()); // Ensure minimum damage of 10
        return (int) (baseDamage * effectiveness);
    }
}
