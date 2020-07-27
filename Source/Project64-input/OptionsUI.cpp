#include "OptionsUI.h"
#include "wtl.h"
#include "resource.h"
#include <Common\StdString.h>

class COptionsDlg :
    public CDialogImpl<COptionsDlg>
{
public:
    enum { IDD = IDD_Options };

    BEGIN_MSG_MAP(COptionsDlg)
        MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        COMMAND_ID_HANDLER(IDOK, OnOkCmd)
        COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
    END_MSG_MAP()

    COptionsDlg(uint32_t ControlIndex, CONTROL & ControlInfo, N64CONTROLLER & Controller) :
        m_ControlIndex(ControlIndex),
        m_ControlInfo(ControlInfo),
        m_Controller(Controller)
    {
    }

    LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        CenterWindow(GetParent());
        SetWindowText(stdstr_f("Options - Player %d", m_ControlIndex + 1).ToUTF16().c_str());
        CButton(GetDlgItem(IDC_REAL_N64_RANGE)).SetCheck(m_Controller.RealN64Range ? BST_CHECKED : BST_UNCHECKED);
        return TRUE;
    }
    LRESULT OnOkCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        bool bChanged = false;
        bool RealN64Range = CButton(GetDlgItem(IDC_REAL_N64_RANGE)).GetCheck() == BST_CHECKED;
        if (RealN64Range != m_Controller.RealN64Range)
        {
            m_Controller.RealN64Range = RealN64Range;
            bChanged = true;
        }
        if (bChanged)
        {
            GetParent().SendMessage(PSM_CHANGED);
        }
        EndDialog(wID);
        return 0;
    }
    LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        EndDialog(wID);
        return 0;
    }
    uint32_t m_ControlIndex;
    CONTROL & m_ControlInfo;
    N64CONTROLLER & m_Controller;
};

void ConfigOption(uint32_t ControlIndex, CONTROL & ControlInfo, N64CONTROLLER & Controller)
{
    COptionsDlg(ControlIndex, ControlInfo, Controller).DoModal();
}