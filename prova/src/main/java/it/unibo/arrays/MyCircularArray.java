package it.unibo.arrays;

class MyCircularArray {

    int[] array;
    private int pos = 0;

    MyCircularArray() {
        this.array = new int[10];
    }

    MyCircularArray(int size) {
        this.array = new int[size];
    }

    void add(final int elem) {
        if(this.pos < array.length){
            array[this.pos] = elem;
            this.pos += 1;
        }
        else{
            this.pos -= array.length;
            array[this.pos] = elem;
            this.pos += 1;
        }
    }

    void reset() {
        for(int i = 0; i < this.array.length; ++i){
            array[i] = 0;
        }
        this.pos = 0;
    }

    void printArray() {
        System.out.print("[");
        for (int i = 0; i < this.array.length - 1; i++) {
            System.out.print(this.array[i] + ",");
        }
        System.out.print(this.array[this.array.length - 1] + "]");
    }

    public static void main(final String[] args) {

        // 1) Creare un array circolare di dieci elementi
        MyCircularArray circularArray = new MyCircularArray();

        // 2) Aggiungere gli elementi da 1 a 10 e stampare il contenuto
        // dell'array circolare
        for(int i = 0; i < circularArray.array.length; ++i){
            circularArray.add(i + 1);
        }
        circularArray.printArray();

        // 3) Aggiungere gli elementi da 11 a 15 e stampare il contenuto
        // dell'array circolare
        for(int i = 11; i < 16; ++i){
            circularArray.add(i);
        }
        circularArray.printArray();

        // 4) Invocare il metodo reset
        circularArray.reset();

        // 5) Stampare il contenuto dell'array circolare
        circularArray.printArray();

        // 6) Aggiungere altri elementi a piacere e stampare il contenuto
        // dell'array circolare
        for(int i = 23; i < 57; ++i){
            circularArray.add(i);
        }
        circularArray.printArray();
    }
}
