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
        return 0;
    }
    
    final public ComplexNumber plus(final ComplexNumber other) {
        return null;
    }
    
    public ComplexNumber sub(final ComplexNumber other) {
        return null;
    }

    public ComplexNumber times(final ComplexNumber other) {
        return null;
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