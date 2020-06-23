package systemUI;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;

import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JOptionPane;
import javax.swing.table.DefaultTableModel;

import Users.Operator;

public class OperatorFileList extends FileListUI {

	private static final long serialVersionUID = 1L;

	private JButton upload;
	private String sFileName;
	private Operator user;

	public OperatorFileList(Operator user) {
		super(user);
		this.user = user;

		upload = new JButton("上传文件");
		upload.setFont(font);
		select.add(upload);
		upload.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				JFileChooser f = new JFileChooser(new File("d://"));
				f.showDialog(OperatorFileList.this, "选择文件");
				File file = f.getSelectedFile();
				if (file == null)
				{
					JOptionPane.showMessageDialog(OperatorFileList.this, "请先选择文件", "提示", JOptionPane.INFORMATION_MESSAGE);
				} 
				else
				{
					sFileName = file.getName();
					new UploadUI(OperatorFileList.this, sFileName);
				}
			}
		});
	}

	public Operator getUer() {
		return user;
	}

	public void addrow(String ID, String name, String creator, String time, String description) {
		String[] info = new String[5];
		info[0] = ID;
		info[1] = name;
		info[2] = creator;
		info[3] = time;
		info[4] = description;
		DefaultTableModel tableModel = (DefaultTableModel) table.getModel();
		tableModel.addRow(info);
	}
}
