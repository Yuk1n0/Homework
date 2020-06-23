package AboutFile;

import java.io.Serializable;
import java.util.Calendar;

public class Doc implements Serializable{

	private static final long serialVersionUID = 1L;

	private String ID;
	private String filename;
	private String creator;
	private Calendar timestamp;
	private String description;

	public Doc(String iD, String filename, String creator, Calendar timestamp, String description) {
		ID = iD;
		this.creator = creator;
		this.timestamp = timestamp;
		this.description = description;
		this.filename = filename;
	}	

	@Override
	public String toString() {
		return "Doc [ID=" + ID + ", filename=" + filename + ", creator=" + creator + ", timestamp=" + timestamp
				+ ", description=" + description + "]";
	}

	public String getID() {
		return ID;
	}
	public void setID(String iD) {
		ID = iD;
	}
	public String getCreator() {
		return creator;
	}
	public void setCreator(String creator) {
		this.creator = creator;
	}
	public Calendar getTimestamp() {
		return timestamp;
	}
	public void setTimestamp(Calendar timestamp) {
		this.timestamp = timestamp;
	}
	public String getDescription() {
		return description;
	}
	public void setDescription(String description) {
		this.description = description;
	}
	public String getFilename() {
		return filename;
	}
	public void setFilename(String filename) {
		this.filename = filename;
	}
}
