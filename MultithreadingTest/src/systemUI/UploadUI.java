package systemUI;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.FileNotFoundException;
import java.io.IOException;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;

import Operation.DataException;
import Users.Operator;

public class UploadUI extends JFrame implements ActionListener {

	private static final long serialVersionUID = 1L;

	private JButton sure = new JButton("确认"), cancel = new JButton("取消");
	private JTextField ID = new JTextField(), description = new JTextField(), filename = new JTextField();
	private JLabel inID = new JLabel("请输入文件ID："), inDesc = new JLabel("请输入文件描述："),name= new JLabel("文件名：");
	private JPanel jp = new JPanel(), bottom = new JPanel();
	private Font font;
	private String sFileName;
	private Operator user;
	private OperatorFileList list;

	public UploadUI(OperatorFileList filelist, String filepath) {
		list = filelist;
		user = list.getUer();
		sFileName = filepath;
		font = new Font("宋体", Font.PLAIN, 24);

		sure.setFont(font);
		cancel.setFont(font);
		sure.addActionListener(this);
		cancel.addActionListener(this);

		name.setFont(font);
		filename.setText(sFileName);
		filename.setEditable(false);
		filename.setFont(font);
		inID.setFont(font);
		ID.setFont(font);
		description.setFont(font);
		inDesc.setFont(font);
		jp.setLayout(new GridLayout(3, 3));
		jp.setSize(new Dimension(500, 600));
		jp.add(name);
		jp.add(filename);
		jp.add(inID);
		jp.add(ID);
		jp.add(inDesc);
		jp.add(description);
		this.add(jp);

		bottom.add(sure);
		bottom.add(cancel);
		this.add(bottom,BorderLayout.SOUTH);
		this.setVisible(true);
		this.pack();
		this.setLocationRelativeTo(null);
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		if(e.getSource() == sure) {
			try {
				user.uploadFile(ID.getText(), sFileName, description.getText());
				JOptionPane.showMessageDialog(UploadUI.this, "文件上传成功！", "提示", JOptionPane.INFORMATION_MESSAGE);
				java.util.Calendar presenttime = java.util.Calendar.getInstance();   
				java.text.SimpleDateFormat f =new java.text.SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
				list.addrow(ID.getText(), sFileName, user.getName(), f.format(presenttime.getTime()),description.getText());
				this.dispose();
			} catch (FileNotFoundException e1) {
				JOptionPane.showMessageDialog(UploadUI.this, "未找到相应文件！", "提示", JOptionPane.INFORMATION_MESSAGE);
			} catch (DataException e1) {
				JOptionPane.showMessageDialog(UploadUI.this, e1.getString(), "提示", JOptionPane.INFORMATION_MESSAGE);
			} catch (IOException e1) {
				JOptionPane.showMessageDialog(UploadUI.this, "文件上传失败！", "提示", JOptionPane.INFORMATION_MESSAGE);
			}
		}
		else if(e.getSource() == cancel) {
			this.setVisible(false);
		}
	}
}
