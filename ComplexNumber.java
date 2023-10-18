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

    public ComplexNumber times(final ComplexNumber b) {
        double parteReale = (this.getReal() * b.getReal()) - (this.getImaginary() * b.getImaginary());
        double parteImmaginaria = (this.getReal() * b.getImaginary()) + (this.getImaginary() * b.getReal());
        return new ComplexNumber(parteReale, parteImmaginaria);
    }

    public ComplexNumber div(final ComplexNumber other) {
        final double commonDenominator = other.getReal() * other.getReal() + other.getImaginary() * other.getImaginary();
        final double realNumerator = this.getReal() * other.getReal() + this.getImaginary() * other.getImaginary();
        final double imaginaryNumerator = other.getReal() * this.getImaginary() - this.getReal() * other.getImaginary();
        return new ComplexNumber(realNumerator / commonDenominator, imaginaryNumerator / commonDenominator);
    }

    public String toString() {
        return this.getReal() + " " + this.getImaginary();
    }
    
    static public void main(String[] args){
        ComplexNumber number = new ComplexNumber(4, 8);
        ComplexNumber number2;
        number2 = number.sub(new ComplexNumber(10, 3), new ComplexNumber(6, 9));
        ComplexNumber number3 = new ComplexNumber(5, 10);
        ComplexNumber somma = number.plus(number3); 
        System.out.print(somma.getReal() + " ");
        System.out.println(somma.getImaginary());
        ComplexNumber prodotto = number.times(number2);
        System.out.print(prodotto.getReal() + " ");
        System.out.println(prodotto.getImaginary());
        String stringa = number.toString();
        System.out.println(stringa); 
    }
}