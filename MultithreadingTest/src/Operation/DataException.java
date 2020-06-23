package Operation;

public class DataException extends Exception {

	private static final long serialVersionUID = 1L;

	private String string;

	public DataException(String string) {
		this.string = string;
	}

	public String getString() {
		return string;
	}

	public void setString(String string) {
		this.string = string;
	}
}
