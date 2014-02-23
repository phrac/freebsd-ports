PORTNAME=	tox-core
PORTVERSION=	20140223
CATEGORIES=	net-im
MASTER_SITES=	GH

MAINTAINER=	derek@disflux.com
COMMENT=	A free as in freedom Skype replacement.

LICENSE=	GPLv3

USE_GITHUB=	yes
GH_ACCOUNT=	irungentoo
GH_PROJECT=	ProjectTox-Core
GH_COMMIT=	f219fb4
GH_TAGNAME=	${GH_COMMIT}

DIST_SUBDIR=	${PORTNAME}

USE_AUTOTOOLS=	autoconf

LIB_DEPENDS=   libsodium.so:${PORTSDIR}/security/libsodium

pre-configure:
	@cd ${WRKSRC} && ${SH} autogen.sh

.include <bsd.port.mk>
