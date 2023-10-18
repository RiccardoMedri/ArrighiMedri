class ComplexNumber {
    private final double real;
    private final double imaginary;

    public ComplexNumber(final double real, final double imaginary) {
        this.real = real;
        this.imaginary = imaginary;
    }

    public double getImaginary() {
        return this.imaginary;
    }

    public double getReal() {
        return this.real;
    }
    
    public ComplexNumber plus(final ComplexNumber a) {
        double parteReale = this.getReal() + a.getReal();
        double parteImmaginaria = this.getImaginary() + a.getImaginary();
        return new ComplexNumber(parteReale, parteImmaginaria);
    }
    
    public ComplexNumber sub(final ComplexNumber a, final ComplexNumber b) {
        ComplexNumber sottrazione = new ComplexNumber((a.getReal() - b.getReal()), (a.getImaginary() - b.getImaginary()));
        return sottrazione;
    }

    public double times(final ComplexNumber a, final ComplexNumber b) {
        double moltiplicazione = ((a.getReal() * b.getReal()) - (a.getImaginary() * b.getImaginary())) + ((a.getReal() * b.getImaginary()) + (a.getImaginary() * b.getReal()));
        return moltiplicazione;
    }

    public ComplexNumber div(final ComplexNumber other) {
        final double commonDenominator = other.getReal() * other.getReal() + other.getImaginary() * other.getImaginary();
        final double realNumerator = this.getReal() * other.getReal() + this.getImaginary() * other.getImaginary();
        final double imaginaryNumerator = other.getReal() * this.getImaginary() - this.getReal() * other.getImaginary();
        return new ComplexNumber(realNumerator / commonDenominator, imaginaryNumerator / commonDenominator);
    }

    static public void main(String[] args){
        ComplexNumber number = new ComplexNumber(4, 8);
<<<<<<< HEAD
        ComplexNumber number2;

        number2 = number.sub(new ComplexNumber(10, 3), new ComplexNumber(6, 9));
=======
        ComplexNumber number3 = new ComplexNumber(5, 10);
        ComplexNumber somma = number.plus(number3); 
        System.out.println(somma.getReal());
        System.out.println(somma.getImaginary());

>>>>>>> 133af1dd9221afcc850366f2a72af0ed317e3848
    }
}