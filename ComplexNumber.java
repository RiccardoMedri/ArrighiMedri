class ComplexNumber {
    private final double real;
    private final double imaginary;

    public ComplexNumber(final double real, final double imaginary) {
        this.real = real;
        this.imaginary = imaginary;
    }

    public ComplexNumber (final double numero) {
        
    }

    public double getImaginary() {
        return imaginary;
    }

    public double getReal() {
        return this.real;
    }
    
    public ComplexNumber plus(final ComplexNumber a, final ComplexNumber b) {
        double somma = (a.getReal() + b.getReal()) + (a.getImaginary() + b.getImaginary());
        return new ComplexNumber (somma);
    }
    
    public ComplexNumber sub(final ComplexNumber a, final ComplexNumber b) {
        ComplexNumber sottrazione = (a.getReal() - b.getReal()) - (a.getImaginary() - b.getImaginary());
        return sottrazione;
    }

    public ComplexNumber times(final ComplexNumber other) {
        ComplexNumber moltiplicazione = ((a.getReal() * b.getReal()) - (a.getImaginary() * b.getImaginary())) + ((a.getReal() * b.getImaginary()) + (a.getImaginary() * b.getReal()));
        return moltiplicazione;
    }

    public ComplexNumber div(final ComplexNumber other) {
        final double commonDenominator = other.getReal() * other.getReal() + other.getImaginary() * other.getImaginary();
        final double realNumerator = this.getReal() * other.getReal() + this.getImaginary() * other.getImaginary();
        final double imaginaryNumerator = other.getReal() * this.getImaginary() - this.getReal() * other.getImaginary();
        return new ComplexNumber(realNumerator / commonDenominator, imaginaryNumerator / commonDenominator);
    }

    static public void main(String[] args){
        // main vuoto
    }
}