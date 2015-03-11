
public class HelloJNI {
    static {
        // Load native library
        System.loadLibrary("hello");
    }

    private native void sayHello();

    public static void main(String[] args) {
        HelloJNI jniTest = new HelloJNI();
        jniTest.sayHello();
    }
}
