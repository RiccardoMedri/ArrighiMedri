class ComplexNumber {
    private final double real;
    private final double imaginary;

    public ComplexNumber(final double real, final double imaginary) {
        this.real = real;
        this.imaginary = imaginary;
    }

    public double getImaginary() {
        return imaginary;
    }

    public double getReal() {
        return this.real;
    }

    final public ComplexNumber plus(final ComplexNumber a, final ComplexNumber b) {
        double somma = (a.real + b.real) + (a.imaginary + b.imaginary);
        return somma;
    }
    
    public ComplexNumber sub(final ComplexNumber a, final ComplexNumber b) {
        double sottrazione = (a.real - b.real) - (a.imaginary - b.imaginary);
        return sottrazione;
    }

    public ComplexNumber times(final ComplexNumber other) {
        double moltiplicazione = 
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
    }
}