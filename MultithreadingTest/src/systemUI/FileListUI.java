package systemUI;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.FileNotFoundException;
import java.io.IOException;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.SwingUtilities;
import javax.swing.table.DefaultTableCellRenderer;
import javax.swing.table.DefaultTableModel;

import Operation.DataException;
import Operation.Main;
import Users.*;

public class FileListUI extends JFrame implements ActionListener{

	private static final long serialVersionUID = 1L;

	private int width;
	private int height;
	private String[][] cellData;
	private String[] columnNames = {"文件ID", "文件名", "上传者", "上传时间", "文件描述"};
	private User user;

	private JLabel listname;
	protected DefaultTableModel tableModel;
	protected JTable table;
	private JScrollPane scrollPane;
	private JButton download, exit; 
	protected JPanel select;
	protected Font font;

	public FileListUI(User user) {
		this.user = user;
		this.width = 5;
		this.height = Main.docs.size();
		cellData = new String[height][width];
		cellData = user.FileTable();

		this.setLayout(new BorderLayout(5, 5));
		font = new Font("宋体", Font.BOLD, 40);

		listname = new JLabel("文件列表",SwingUtilities.CENTER);
		listname.setFont(font);
		this.add(BorderLayout.NORTH, listname);

		tableModel = new DefaultTableModel(cellData, columnNames){
			private static final long serialVersionUID = 1L;
			public boolean isCellEditable(int row, int column) {
				return false;
			}			
		};

		table = new JTable();
		table.setModel(tableModel);	
		table.setPreferredScrollableViewportSize(new Dimension(1200,500));
		font = new Font("宋体", Font.PLAIN, 24);
		table.getTableHeader().setFont(font);
		font = new Font("宋体", Font.PLAIN, 24);
		table.setFont(font);
		table.setRowHeight(32);
		DefaultTableCellRenderer tcr = new DefaultTableCellRenderer();// 设置table内容居中
		tcr.setHorizontalAlignment(JLabel.CENTER);
		table.setDefaultRenderer(Object.class, tcr);
		table.setAutoResizeMode(JTable.AUTO_RESIZE_ALL_COLUMNS);
		table.setSelectionMode(javax.swing.ListSelectionModel.SINGLE_SELECTION);

		scrollPane = new JScrollPane();
		scrollPane.setSize(750, 10);
		scrollPane.setViewportView(table);
		this.add(scrollPane, BorderLayout.CENTER);

		download = new JButton("下载文件");
		exit = new JButton("返回");
		font = new Font("宋体", Font.PLAIN, 28); 
		download.setFont(font);
		exit.setFont(font);
		select = new JPanel();
		select.add(download);
		select.add(exit);

		this.add(select, BorderLayout.SOUTH);
		this.setTitle(this.user.getName());
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.pack();
		this.setVisible(true);
		this.setLocationRelativeTo(null);

		download.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				int currentRow = table.getSelectedRow();
				if(currentRow == -1) {
					JOptionPane.showMessageDialog(FileListUI.this, "请先选择一行", "提示", JOptionPane.INFORMATION_MESSAGE);
					return;
				}
				String ID = (String) tableModel.getValueAt(currentRow, 0);
				try {
					user.downloadFile(ID);
					JOptionPane.showMessageDialog(FileListUI.this, "文件下载成功！", "提示", JOptionPane.INFORMATION_MESSAGE);
				} catch (FileNotFoundException e1) {
					JOptionPane.showMessageDialog(FileListUI.this, "未找到相应文件！", "提示", JOptionPane.INFORMATION_MESSAGE);
				} catch (DataException e1) {
					JOptionPane.showMessageDialog(FileListUI.this, e1.getString(), "提示", JOptionPane.INFORMATION_MESSAGE);
				} catch (IOException e1) {
					JOptionPane.showMessageDialog(FileListUI.this, "文件下载失败！", "提示", JOptionPane.INFORMATION_MESSAGE);
				}
			}
		});

		exit.addActionListener(this);
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		if (e.getSource() == exit) {
			this.dispose();
			if(user.getRole().equals("Administrator")) {
				new AdministratorUI(user);
			}
			else {
				new UserUI(user);
			}
		}
	}
}
